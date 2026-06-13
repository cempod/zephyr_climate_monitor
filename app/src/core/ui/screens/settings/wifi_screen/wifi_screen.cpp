#include "wifi_screen.hpp"
#include "param_machine.hpp"
#include "screen_manager.hpp"
#include "event_machine.hpp"

#include "style_manager.hpp"

#include <cstddef>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(wifi_scan, LOG_LEVEL_INF);

WifiScreen* WifiScreen::instance = nullptr;

WifiScreen& WifiScreen::get() {
    static WifiScreen screen;
    return screen;
}

void WifiScreen::update_aps(wifi_scan_result *entry) {
    if (entry == NULL) {
        LOG_INF("Scan finished. Found %d APs", ap_count);
        is_scanning = false;
        return;
    }
    if (ap_count < MAX_AP) {
        memset(&scanned_aps[ap_count], 0, sizeof(struct wifi_ap_info));
        memcpy(scanned_aps[ap_count].ssid, entry->ssid, entry->ssid_length);
        scanned_aps[ap_count].ssid[entry->ssid_length] = '\0';
        scanned_aps[ap_count].rssi = entry->rssi;
        scanned_aps[ap_count].channel = entry->channel;
        scanned_aps[ap_count].is_open = (entry->security == WIFI_SECURITY_TYPE_NONE);
        ap_count++;

        LOG_INF("Found: %s (%d dBm)", scanned_aps[ap_count-1].ssid, entry->rssi);
    }
}

static void wifi_mgmt_event_handler(struct net_mgmt_event_callback *cb,
                                    uint64_t mgmt_event, struct net_if *iface) {
    if (mgmt_event == NET_EVENT_WIFI_SCAN_RESULT) {
        struct wifi_scan_result *entry = (struct wifi_scan_result *)cb->info;
        WifiScreen::get().update_aps(entry);
    } 
    else if (mgmt_event == NET_EVENT_WIFI_SCAN_DONE) {
        WifiScreen::get().update_aps(NULL);
    }
}

void WifiScreen::start_wifi_scan(void) {
    LOG_INF("Starting WiFi scan...");
    int ret = net_mgmt(NET_REQUEST_WIFI_SCAN, iface, NULL, 0);
	if (ret) {
		printk("WiFi scan request failed: %d\n", ret);
        is_scanning = false;
	} else {
        lv_obj_clean(wifi_list);
        is_scanning = true;
        ap_count = 0;
        current_page = 0;
    }
}

static void update_button_event_handler(lv_event_t * e) {
    WifiScreen::get().start_wifi_scan();
}

static void next_button_event_handler(lv_event_t * e) {
    WifiScreen::get().change_list_page(WifiScreen::PAGE_NEXT);
}

static void back_button_event_handler(lv_event_t * e) {
    WifiScreen::get().change_list_page(WifiScreen::PAGE_BACK);
}

WifiScreen::WifiScreen() {
    instance = this;
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    wifi_list = lv_list_create(screen);
    lv_obj_set_size(wifi_list, 480, 260);
    lv_obj_align(wifi_list, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_clear_flag(wifi_list, LV_OBJ_FLAG_SCROLLABLE);

    exit_button = lv_button_create(screen);
    lv_obj_set_size(exit_button, 120, 60);
    lv_obj_align(exit_button, LV_ALIGN_BOTTOM_LEFT, 0, 0);
    lv_obj_t * exit_button_label = lv_label_create(exit_button);
    lv_obj_center(exit_button_label);
    lv_label_set_text(exit_button_label, "Exit");
    lv_obj_add_style(exit_button, StyleManager::get().get_button_style(), 0);

    update_button = lv_button_create(screen);
    lv_obj_set_size(update_button, 120, 60);
    lv_obj_align(update_button, LV_ALIGN_BOTTOM_LEFT, 120, 0);
    lv_obj_t * update_button_label = lv_label_create(update_button);
    lv_obj_center(update_button_label);
    lv_label_set_text(update_button_label, "Update");
    lv_obj_add_style(update_button, StyleManager::get().get_button_style(), 0);
    lv_obj_add_state(update_button, LV_STATE_DISABLED);
    lv_obj_add_event_cb(update_button, update_button_event_handler, LV_EVENT_RELEASED, NULL);

    next_button = lv_button_create(screen);
    lv_obj_set_size(next_button, 120, 60);
    lv_obj_align(next_button, LV_ALIGN_BOTTOM_RIGHT, 0, 0);
    lv_obj_t * next_button_label = lv_label_create(next_button);
    lv_obj_center(next_button_label);
    lv_label_set_text(next_button_label, ">");
    lv_obj_add_style(next_button, StyleManager::get().get_button_style(), 0);
    lv_obj_add_event_cb(next_button, next_button_event_handler, LV_EVENT_RELEASED, NULL);

    back_button = lv_button_create(screen);
    lv_obj_set_size(back_button, 120, 60);
    lv_obj_align(back_button, LV_ALIGN_BOTTOM_RIGHT, -120, 0);
    lv_obj_t * back_button_label = lv_label_create(back_button);
    lv_obj_center(back_button_label);
    lv_label_set_text(back_button_label, "<");
    lv_obj_add_style(back_button, StyleManager::get().get_button_style(), 0);
    lv_obj_add_event_cb(back_button, back_button_event_handler, LV_EVENT_RELEASED, NULL);

    iface = net_if_get_default();

    if (!iface) {
		LOG_INF("No network interface\n");
	}
    
    ap_count = 0;
    memset(scanned_aps, 0, sizeof(scanned_aps));

    net_mgmt_init_event_callback(&scan_cb, wifi_mgmt_event_handler,
                                NET_EVENT_WIFI_SCAN_RESULT | NET_EVENT_WIFI_SCAN_DONE);
    net_mgmt_add_event_callback(&scan_cb);

    start_wifi_scan();
}

void WifiScreen::update_callbacks() {}

void WifiScreen::change_list_page(page_command command) {
    uint8_t total_pages = (ap_count + AP_ON_PAGE - 1) / AP_ON_PAGE;

    switch (command) {
        case PAGE_NEXT: {
            if (current_page < total_pages) {
                current_page++;
            } else {
                current_page = 1;   
            }
            break;
        }
        case PAGE_BACK: {
            if (current_page > 1) {
                current_page--;
            } else {
                current_page = total_pages;
            }
            break;
        }
    };

    uint8_t start = (current_page - 1) * AP_ON_PAGE;
    uint8_t end = start + AP_ON_PAGE;
    if (end > ap_count) {
        end = ap_count;
    }

    lv_obj_clean(wifi_list);
    char buf[64];

    for (uint8_t i = start; i < end; i++) {
        snprintf(buf, sizeof(buf), "%s", scanned_aps[i].ssid);
        lv_list_add_button(wifi_list, LV_SYMBOL_WIFI, buf);
    }
}

void WifiScreen::update() {
    if (is_scanning) {
        lv_obj_add_state(update_button, LV_STATE_DISABLED);
    } else {
        lv_obj_remove_state(update_button, LV_STATE_DISABLED);
    }

    if (ap_count <= AP_ON_PAGE) {
        lv_obj_add_state(back_button, LV_STATE_DISABLED);
        lv_obj_add_state(next_button, LV_STATE_DISABLED);
    } else {
        lv_obj_remove_state(back_button, LV_STATE_DISABLED);
        lv_obj_remove_state(next_button, LV_STATE_DISABLED);
    }

    if (!is_scanning && current_page == 0) {
        change_list_page(PAGE_NEXT);
        LOG_INF("WiFi list updated");
    }
    
}