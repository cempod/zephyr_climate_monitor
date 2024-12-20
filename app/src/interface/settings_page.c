#include "settings_page.h"
#include "colors/colors.h"
#include "func.h"

#ifndef SIMULATOR
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/rtc.h>

const struct device *const rtc_device = DEVICE_DT_GET(DT_ALIAS(rtc));

static uint8_t year_codes[] = {2,3,4,5,0,1};
static uint8_t month_codes[] = {6,2,2,5,0,3,5,1,4,6,2,4};
static uint8_t leap_month_codes[] = {5,1,2,5,0,3,5,1,4,6,2,4};

static void setup_date(int day, int month, int year) {
    struct rtc_time tm;
    rtc_get_time(rtc_device, &tm);
    tm.tm_year = year - 1900;
    tm.tm_mon = month - 1;
    tm.tm_mday = day;

    if(year-2024==0 || year-2024==4) {
        tm.tm_wday = ((day + leap_month_codes[month - 1] + year_codes[year-2024]) % 7)-1;
    } else {
        tm.tm_wday = ((day + month_codes[month - 1] + year_codes[year-2024]) % 7)-1;
    }
    
    if(tm.tm_wday == -1) {
        tm.tm_wday = 6;
    }
    rtc_set_time(rtc_device, &tm);
}

static void setup_time(int hour, int minute) {
    struct rtc_time tm;
    rtc_get_time(rtc_device, &tm);
    tm.tm_hour = hour;
    tm.tm_min = minute;
    tm.tm_sec = 0;
    rtc_set_time(rtc_device, &tm);
}

#endif

void place_settings_top_panel(settings_top_panel_t * panel, lv_obj_t * parent);
void set_settings_top_panel_theme(settings_top_panel_t * panel);
void place_menu(menu_card_t * menu_card, lv_obj_t * parent);
void set_menu_theme(menu_card_t * menu_card);
void add_date_page(setup_date_page_t * page);
void set_date_page_theme(setup_date_page_t * page);
void add_time_page(setup_time_page_t * page);
void set_time_page_theme(setup_time_page_t * page);
void change_roller_days(void);

const char * hours = "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23";
const char * minutes = "00\n01\n02\n03\n04\n05\n06\n07\n08\n09\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31\n32\n33\n34\n35\n36\n37\n38\n39\n40\n41\n42\n43\n44\n45\n46\n47\n48\n49\n50\n51\n52\n53\n54\n55\n56\n57\n58\n59";
const char * days_31 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31";
const char * days_30 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30";
const char * days_29 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29";
const char * days_28 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28";
const char * months = "Январь\nФевраль\nМарт\nАпрель\nМай\nИюнь\nИюль\nАвгуст\nСентябрь\nОктябрь\nНоябрь\nДекабрь";
const char * years = "2024\n2025\n2026\n2027\n2028\n2029";

static int current_hour, current_minute, current_day, current_month, current_year;

static lv_obj_t * settings_screen;

static settings_top_panel_t settings_top_panel = {
    .x_size = 470,
    .y_size = 40,
    .x_offset = 5,
    .y_offset = 5,
};

menu_card_t menu_card = {
    .x_size = 470,
    .y_size = 260,
    .x_offset = 5,
    .y_offset = 55,
};

static setup_date_page_t setup_date_page;
static setup_time_page_t setup_time_page;

void
init_settings_page() {
    settings_screen = lv_obj_create(NULL);
    place_settings_top_panel(&settings_top_panel, settings_screen);
    place_menu(&menu_card, settings_screen);
    update_settings_date_time(0, 0, 1, 1, 2024);
}

void
load_settings_page() {
    lv_scr_load(settings_screen);
    lv_roller_set_selected(setup_time_page.hour_roller, current_hour, LV_ANIM_ON);
    lv_roller_set_selected(setup_time_page.minute_roller, current_minute, LV_ANIM_ON);
    lv_roller_set_selected(setup_date_page.month_roller, current_month-1, LV_ANIM_ON);
    lv_roller_set_selected(setup_date_page.day_roller, current_day-1, LV_ANIM_ON);
    if(current_year-2024 >= 0 && current_year-2024 <= 5) {
        lv_roller_set_selected(setup_date_page.year_roller, current_year-2024, LV_ANIM_ON);
    }
    change_roller_days();
}

void
set_settings_page_theme(int theme) {
    lv_obj_set_style_bg_color(settings_screen, get_colors().background_color, 0);
    set_settings_top_panel_theme(&settings_top_panel);
    set_menu_theme(&menu_card);
}

static void back_button_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        load_main_page();
    }
}

void 
place_settings_top_panel(settings_top_panel_t * panel, lv_obj_t * parent) {
    panel->card = lv_obj_create(parent);
    lv_obj_align(panel->card, LV_ALIGN_TOP_LEFT, panel->x_offset, panel->y_offset);
    lv_obj_set_size(panel->card, panel->x_size, panel->y_size);
    lv_obj_set_style_pad_all(panel->card,0,0);
    panel->panel_label = place_label(0,0, panel->card, get_colors().main_font);
    panel->back_button = lv_btn_create(panel->card);
    lv_obj_clear_state(panel->back_button, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(panel->back_button, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(panel->back_button, 1, 0);
    lv_obj_set_style_pad_all(panel->back_button, 3, 0);
    lv_obj_align(panel->back_button, LV_ALIGN_RIGHT_MID, -3, 0);
    panel->back_button_label = place_label(0,0, panel->back_button, get_colors().main_font);
    set_label_text(panel->back_button_label, "Назад");
    set_label_text(panel->panel_label, "Настройки");
    set_settings_top_panel_theme(panel);
    lv_obj_add_event_cb(panel->back_button, back_button_event_handler, LV_EVENT_CLICKED, NULL);
    set_settings_top_panel_theme(&settings_top_panel);
}

void
set_settings_top_panel_theme(settings_top_panel_t * panel) {
    lv_obj_set_style_bg_color(panel->card, get_colors().header_color, 0);
    lv_obj_set_style_border_color(panel->card, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(panel->back_button, get_colors().header_color, 0);
    lv_obj_set_style_border_color(panel->back_button, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->panel_label, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->back_button_label, get_colors().header_font_color, 0);
}

void
place_menu(menu_card_t * menu_card, lv_obj_t * parent) {
    menu_card->card = lv_obj_create(parent);
    lv_obj_align(menu_card->card, LV_ALIGN_TOP_LEFT, menu_card->x_offset, menu_card->y_offset);
    lv_obj_set_size(menu_card->card, menu_card->x_size, menu_card->y_size);
    lv_obj_set_style_pad_all(menu_card->card,0,0);
    menu_card->tab_view = lv_tabview_create(menu_card->card, LV_DIR_LEFT, 80);
    lv_obj_clear_flag(lv_tabview_get_content(menu_card->tab_view), LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_set_style_border_side(lv_tabview_get_tab_btns(menu_card->tab_view), LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().main_font ,LV_PART_ITEMS);
    lv_obj_t * setup_time_tab = lv_tabview_add_tab(menu_card->tab_view, "Время");
    setup_time_page.parent = setup_time_tab;
    add_time_page(&setup_time_page);
    lv_obj_t * setup_date_tab = lv_tabview_add_tab(menu_card->tab_view, "Дата");
    setup_date_page.parent = setup_date_tab;
    add_date_page(&setup_date_page);
    
    /*lv_obj_t * tab1 = */
    /*lv_obj_t * tab2 = */lv_tabview_add_tab(menu_card->tab_view, "Экран");
    set_menu_theme(menu_card);
}

void
set_menu_theme(menu_card_t * menu_card) {
    lv_obj_set_style_bg_color(menu_card->card, get_colors().background_color, 0);
    lv_obj_set_style_border_color(menu_card->card, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(menu_card->tab_view, get_colors().background_color, 0);
    lv_obj_set_style_bg_color(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().header_color, 0);
    lv_obj_set_style_text_color(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().header_font_color, 0);
    lv_obj_set_style_border_color(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().header_font_color, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_color(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().header_font_color, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_bg_color(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().header_color, LV_PART_ITEMS | LV_STATE_CHECKED);
    set_date_page_theme(&setup_date_page);
    set_time_page_theme(&setup_time_page);
}

void
change_roller_days() {
    static int selected_day;
    selected_day = lv_roller_get_selected(setup_date_page.day_roller);
    switch (lv_roller_get_selected(setup_date_page.month_roller))
        {
        case 1:
            if(lv_roller_get_selected(setup_date_page.year_roller)==0 || lv_roller_get_selected(setup_date_page.year_roller)==4) {
                lv_roller_set_options(setup_date_page.day_roller, days_29, LV_ROLLER_MODE_INFINITE);
                if(selected_day<29) {
                    lv_roller_set_selected(setup_date_page.day_roller, selected_day, LV_ANIM_OFF);
                } else {
                    lv_roller_set_selected(setup_date_page.day_roller, 28, LV_ANIM_ON);
                }
                break;
            }
            lv_roller_set_options(setup_date_page.day_roller, days_28, LV_ROLLER_MODE_INFINITE);
            if(selected_day<28) {
                lv_roller_set_selected(setup_date_page.day_roller, selected_day, LV_ANIM_OFF);
            } else {
                lv_roller_set_selected(setup_date_page.day_roller, 27, LV_ANIM_ON);
            }
            break;
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            lv_roller_set_options(setup_date_page.day_roller, days_31, LV_ROLLER_MODE_INFINITE);
            lv_roller_set_selected(setup_date_page.day_roller, selected_day, LV_ANIM_OFF);
            break;
        
        default:
            lv_roller_set_options(setup_date_page.day_roller, days_30, LV_ROLLER_MODE_INFINITE);
            if(selected_day<30) {
                lv_roller_set_selected(setup_date_page.day_roller, selected_day, LV_ANIM_OFF);
            } else {
                lv_roller_set_selected(setup_date_page.day_roller, 29, LV_ANIM_ON);
            }
            break;
        }
}

static void month_roller_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);
    if(code == LV_EVENT_VALUE_CHANGED) {
        change_roller_days();
    }
}

static void date_save_button_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        #ifndef SIMULATOR
        setup_date(lv_roller_get_selected(setup_date_page.day_roller)+1, lv_roller_get_selected(setup_date_page.month_roller)+1, lv_roller_get_selected(setup_date_page.year_roller)+2024);
        #endif
    }
}

void
add_date_page(setup_date_page_t * page) {
    page->day_roller = lv_roller_create(page->parent);
    lv_obj_align(page->day_roller, LV_ALIGN_CENTER, -105, 0);
    lv_obj_set_size(page->day_roller, 100, 100);
    lv_obj_set_style_text_font(page->day_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->day_roller, days_30, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->day_roller, 3);
    page->month_roller = lv_roller_create(page->parent);
    lv_obj_align(page->month_roller, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(page->month_roller, 100, 100);
    lv_obj_set_style_text_font(page->month_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->month_roller, months, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->month_roller, 3);
    lv_obj_add_event_cb(page->month_roller, month_roller_event_handler, LV_EVENT_ALL, NULL);
    page->year_roller = lv_roller_create(page->parent);
    lv_obj_align(page->year_roller, LV_ALIGN_CENTER, 105, 0);
    lv_obj_set_size(page->year_roller, 100, 100);
    lv_obj_set_style_text_font(page->year_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->year_roller, years, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->year_roller, 3);
    lv_obj_add_event_cb(page->year_roller, month_roller_event_handler, LV_EVENT_ALL, NULL);
    page->save_button = lv_btn_create(page->parent);
    lv_obj_set_height(page->save_button, 40);
    lv_obj_align(page->save_button, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_state(page->save_button, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(page->save_button, LV_OPA_TRANSP, 0);
    page->save_button_label = place_label(0,0, page->save_button, get_colors().main_font);
    set_label_text(page->save_button_label, "Сохранить");
    lv_obj_add_event_cb(page->save_button, date_save_button_event_handler, LV_EVENT_CLICKED, NULL);
    page->label = lv_label_create(page->parent);
    lv_obj_align(page->label, LV_ALIGN_TOP_MID, 0, 7);
    lv_obj_set_style_text_font(page->label, get_colors().main_font, 0);
    set_label_text(page->label, "Установка даты");
    set_date_page_theme(page);
}

void
set_date_page_theme(setup_date_page_t * page) {
    lv_obj_set_style_bg_color(page->month_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->month_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->month_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->month_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->day_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->day_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->day_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->day_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->year_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->year_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->year_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->year_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->save_button, get_colors().header_color, 0);
    lv_obj_set_style_border_color(page->save_button, get_colors().header_color, 0);
    lv_obj_set_style_text_color(page->label, get_colors().header_font_color, 0);
}

static void time_save_button_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        #ifndef SIMULATOR
        setup_time(lv_roller_get_selected(setup_time_page.hour_roller),lv_roller_get_selected(setup_time_page.minute_roller));
        #endif
    }
}

void
add_time_page(setup_time_page_t * page) {
    page->hour_roller = lv_roller_create(page->parent);
    lv_obj_align(page->hour_roller, LV_ALIGN_CENTER, -55, 0);
    lv_obj_set_size(page->hour_roller, 100, 100);
    lv_obj_set_style_text_font(page->hour_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->hour_roller, hours, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->hour_roller, 3);
    page->minute_roller = lv_roller_create(page->parent);
    lv_obj_align(page->minute_roller, LV_ALIGN_CENTER, 55, 0);
    lv_obj_set_size(page->minute_roller, 100, 100);
    lv_obj_set_style_text_font(page->minute_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->minute_roller, minutes, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->minute_roller, 3);
    page->save_button = lv_btn_create(page->parent);
    lv_obj_set_height(page->save_button, 40);
    lv_obj_align(page->save_button, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_clear_state(page->save_button, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(page->save_button, LV_OPA_TRANSP, 0);
    page->save_button_label = place_label(0,0, page->save_button, get_colors().main_font);
    set_label_text(page->save_button_label, "Сохранить");
    lv_obj_add_event_cb(page->save_button, time_save_button_event_handler, LV_EVENT_CLICKED, NULL);
    page->label = lv_label_create(page->parent);
    lv_obj_align(page->label, LV_ALIGN_TOP_MID, 0, 7);
    lv_obj_set_style_text_font(page->label, get_colors().main_font, 0);
    set_label_text(page->label, "Установка времени");
    set_time_page_theme(page);
}

void
set_time_page_theme(setup_time_page_t * page) {
    lv_obj_set_style_bg_color(page->hour_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->hour_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->hour_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->hour_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->minute_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->minute_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->minute_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->minute_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->save_button, get_colors().header_color, 0);
    lv_obj_set_style_border_color(page->save_button, get_colors().header_color, 0);
    lv_obj_set_style_text_color(page->label, get_colors().header_font_color, 0);
}

void
update_settings_date_time(int hour, int minute, int day, int month, int year) {
    current_hour = hour;
    current_minute = minute;
    current_day = day;
    current_month = month;
    current_year = year;
}