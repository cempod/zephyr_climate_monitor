#include "settings_page.h"
#include "colors/colors.h"
#include "func.h"

void place_settings_top_panel(settings_top_panel_t * panel, lv_obj_t * parent);
void set_settings_top_panel_theme(settings_top_panel_t * panel);
void place_menu(menu_card_t * menu_card, lv_obj_t * parent);
void set_menu_theme(menu_card_t * menu_card);
void add_date_time_page(date_time_page_t * page);
void set_date_time_page_theme(date_time_page_t * page);
void change_roller_days(void);

const char * days_31 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30\n31";
const char * days_30 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29\n30";
const char * days_29 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28\n29";
const char * days_28 = "1\n2\n3\n4\n5\n6\n7\n8\n9\n10\n11\n12\n13\n14\n15\n16\n17\n18\n19\n20\n21\n22\n23\n24\n25\n26\n27\n28";
const char * months = "Январь\nФевраль\nМарт\nАпрель\nМай\nИюнь\nИюль\nАвгуст\nСентябрь\nОктябрь\nНоябрь\nДекабрь";

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

static date_time_page_t date_time_page;

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
    lv_roller_set_selected(date_time_page.month_roller, current_month-1, LV_ANIM_ON);
    lv_roller_set_selected(date_time_page.day_roller, current_day-1, LV_ANIM_ON);
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
    lv_obj_set_style_border_side(lv_tabview_get_tab_btns(menu_card->tab_view), LV_BORDER_SIDE_RIGHT, LV_PART_ITEMS | LV_STATE_CHECKED);
    lv_obj_set_style_text_font(lv_tabview_get_tab_btns(menu_card->tab_view), get_colors().main_font ,LV_PART_ITEMS);
    lv_obj_t * date_time_tab = lv_tabview_add_tab(menu_card->tab_view, "Дата и время");
    date_time_page.parent = date_time_tab;
    add_date_time_page(&date_time_page);
    
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
    set_date_time_page_theme(&date_time_page);
}

void
change_roller_days() {
    static int selected_day;
    selected_day = lv_roller_get_selected(date_time_page.day_roller);
    switch (lv_roller_get_selected(date_time_page.month_roller))
        {
        case 1:
            lv_roller_set_options(date_time_page.day_roller, days_28, LV_ROLLER_MODE_INFINITE);
            if(selected_day<28) {
                lv_roller_set_selected(date_time_page.day_roller, selected_day, LV_ANIM_OFF);
            } else {
                lv_roller_set_selected(date_time_page.day_roller, 27, LV_ANIM_ON);
            }
            break;
        case 0:
        case 2:
        case 4:
        case 6:
        case 7:
        case 9:
        case 11:
            lv_roller_set_options(date_time_page.day_roller, days_31, LV_ROLLER_MODE_INFINITE);
            lv_roller_set_selected(date_time_page.day_roller, selected_day, LV_ANIM_OFF);
            break;
        
        default:
            lv_roller_set_options(date_time_page.day_roller, days_30, LV_ROLLER_MODE_INFINITE);
            if(selected_day<30) {
                lv_roller_set_selected(date_time_page.day_roller, selected_day, LV_ANIM_OFF);
            } else {
                lv_roller_set_selected(date_time_page.day_roller, 29, LV_ANIM_ON);
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

void
add_date_time_page(date_time_page_t * page) {
    page->day_roller = lv_roller_create(page->parent);
    lv_obj_align(page->day_roller, LV_ALIGN_TOP_LEFT, 5, 5);
    lv_obj_set_size(page->day_roller, 100, 100);
    lv_obj_set_style_text_font(page->day_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->day_roller, days_30, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->day_roller, 3);
    page->month_roller = lv_roller_create(page->parent);
    lv_obj_align(page->month_roller, LV_ALIGN_TOP_LEFT, 110, 5);
    lv_obj_set_size(page->month_roller, 100, 100);
    lv_obj_set_style_text_font(page->month_roller, get_colors().main_font , 0);
    lv_roller_set_options(page->month_roller, months, LV_ROLLER_MODE_INFINITE);
    lv_roller_set_visible_row_count(page->month_roller, 3);
    lv_obj_add_event_cb(page->month_roller, month_roller_event_handler, LV_EVENT_ALL, NULL);
    set_date_time_page_theme(page);
}

void
set_date_time_page_theme(date_time_page_t * page) {
    lv_obj_set_style_bg_color(page->month_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->month_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->month_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->month_roller, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(page->day_roller, get_colors().background_color, 0);
    lv_obj_set_style_text_color(page->day_roller, get_colors().header_font_color, 0);
    lv_obj_set_style_bg_color(page->day_roller, get_colors().header_color, LV_PART_SELECTED);
    lv_obj_set_style_border_color(page->day_roller, get_colors().border_color, 0);
}

void
update_settings_date_time(int hour, int minute, int day, int month, int year) {
    current_hour = hour;
    current_minute = minute;
    current_day = day;
    current_month = month;
    current_year = year;
}