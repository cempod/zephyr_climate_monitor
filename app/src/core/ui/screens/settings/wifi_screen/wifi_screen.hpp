#pragma once

#include "screen_base.hpp"


#include <zephyr/net/net_if.h>
#include <zephyr/net/wifi_mgmt.h>

#define MAX_AP 21
#define AP_ON_PAGE 7

class WifiScreen : public ScreenBase {
    struct wifi_ap_info {
        char ssid[33];
        int rssi;
        uint8_t channel;
        bool is_open;
    };

    public:
        static WifiScreen& get();

        enum page_command {
            PAGE_BACK = 0,
            PAGE_NEXT
        };

        void update_callbacks() override;
        void update() override;
        void update_aps(wifi_scan_result *entry);
        void start_wifi_scan(void);
        void change_list_page(page_command command);

    private:
        WifiScreen();
        static WifiScreen* instance;
        
        virtual ~WifiScreen() = default;

        struct net_if *iface = nullptr;

        struct wifi_ap_info scanned_aps[MAX_AP];
        uint8_t ap_count = 0;
        struct net_mgmt_event_callback scan_cb;

        bool is_scanning = false;
        uint8_t current_page = 0;

        lv_obj_t * wifi_list;
        lv_obj_t * exit_button;
        lv_obj_t * update_button;
        lv_obj_t * back_button;
        lv_obj_t * next_button;

};