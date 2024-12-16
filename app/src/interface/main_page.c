#include "main_page.h"
#include "colors/colors.h"

#include <stdio.h>
#include <stdarg.h>

void place_card(card_t * card, lv_obj_t * parent);
void set_card_theme(card_t * card);
void place_datetime_card(datetime_card_t * card, lv_obj_t * parent);
void set_datetime_card_theme(datetime_card_t * card);
void place_top_panel(top_panel_t * panel, lv_obj_t * parent);
void set_top_panel_theme(top_panel_t * panel);
lv_obj_t * place_label(int x_offset, int y_offset, lv_obj_t * parent, const lv_font_t * font);
void set_label_text(lv_obj_t * label, const char* msg, ...);

static lv_obj_t * main_screen;

static card_t temperature_card = {
    .x_size = 200,
    .y_size = 150,
    .x_offset = 5,
    .y_offset = 55,
    .header_string = "Температура"
};

static card_t pressure_card = {
    .x_size = 150,
    .y_size = 100,
    .x_offset = 5,
    .y_offset = 215,
    .header_string = "Давление"
};

static card_t humidity_card = {
    .x_size = 150,
    .y_size = 100,
    .x_offset = 165,
    .y_offset = 215,
    .header_string = "Влажность"
};

static card_t co2_card = {
    .x_size = 150,
    .y_size = 100,
    .x_offset = 325,
    .y_offset = 215,
    .header_string = "CO2"
};

static datetime_card_t datetime_card = {
    .x_size = 260,
    .y_size = 150,
    .x_offset = 215,
    .y_offset = 55
};

top_panel_t top_panel = {
    .x_size = 470,
    .y_size = 40,
    .x_offset = 5,
    .y_offset = 5,
};

void
init_main_page(void) {
    main_screen = lv_obj_create(NULL);
    place_card(&temperature_card, main_screen);
    lv_obj_set_style_text_font(temperature_card.label,get_colors().big_font, 0);
    lv_obj_align(temperature_card.label, LV_ALIGN_CENTER, 0, 18);
    set_temperature(27.36f);
    place_card(&pressure_card, main_screen);
    set_pressure(760);
    place_card(&humidity_card, main_screen);
    set_humidity(45.3);
    place_card(&co2_card, main_screen);
    set_co2(1200);
    place_datetime_card(&datetime_card, main_screen);
    set_date(16, 12);
    set_day_of_week(1);
    set_time(12, 56);
    place_top_panel(&top_panel, main_screen);
    set_label_text(top_panel.status_label, "Показатели в норме");
}

void
load_main_page(void) {
    lv_scr_load(main_screen);
    set_theme(DARK_THEME);
}

void 
place_card(card_t * card, lv_obj_t * parent) {
    card->parent = parent;
    card->card = lv_obj_create(card->parent);
    lv_obj_align(card->card, LV_ALIGN_TOP_LEFT, card->x_offset, card->y_offset);
    lv_obj_set_size(card->card, card->x_size, card->y_size);
    lv_obj_set_style_pad_all(card->card,0,0);
    card->header = lv_obj_create(card->card);
    lv_obj_set_size(card->header, card->x_size-4, 35);
    lv_obj_align(card->header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_side(card->header, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_radius(card->header, 0, 0);
    lv_obj_set_style_pad_all(card->header,0,0);
    card->header_label = place_label(0,0, card->header, get_colors().main_font);
    card->label = place_label(0,21, card->card, get_colors().medium_font);
    set_label_text(card->header_label, card->header_string);
    set_card_theme(card);
}

void
set_card_theme(card_t * card) {
    lv_obj_set_style_bg_color(card->card, get_colors().card_background_color, 0);
    lv_obj_set_style_border_color(card->card, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(card->header, get_colors().header_color, 0);
    lv_obj_set_style_bg_color (card->header , get_colors().header_color, 0);
    lv_obj_set_style_text_color(card->label, get_colors().main_font_color, 0);
    lv_obj_set_style_text_color(card->header_label, get_colors().header_font_color, 0);
}

void 
place_datetime_card(datetime_card_t * card, lv_obj_t * parent) {
    card->card = lv_obj_create(parent);
    lv_obj_align(card->card, LV_ALIGN_TOP_LEFT, card->x_offset, card->y_offset);
    lv_obj_set_size(card->card, card->x_size, card->y_size);
    lv_obj_set_style_pad_all(card->card,0,0);
    card->time_label = place_label(0,0, card->card, get_colors().big_font);
    card->date_top_label = place_label(0,-50, card->card, get_colors().main_font);
    card->date_bottom_label = place_label(0,50, card->card, get_colors().main_font);
    set_datetime_card_theme(card);
}

void
set_datetime_card_theme(datetime_card_t * card) {
    lv_obj_set_style_bg_color(card->card, get_colors().card_background_color, 0);
    lv_obj_set_style_border_color(card->card, get_colors().border_color, 0);
    lv_obj_set_style_text_color(card->date_top_label, get_colors().main_font_color, 0);
    lv_obj_set_style_text_color(card->date_bottom_label, get_colors().main_font_color, 0);
    lv_obj_set_style_text_color(card->time_label, get_colors().main_font_color, 0);
}

void 
place_top_panel(top_panel_t * panel, lv_obj_t * parent) {
    panel->card = lv_obj_create(parent);
    lv_obj_align(panel->card, LV_ALIGN_TOP_LEFT, panel->x_offset, panel->y_offset);
    lv_obj_set_size(panel->card, panel->x_size, panel->y_size);
    lv_obj_set_style_pad_all(panel->card,0,0);
    panel->tile_view = lv_tileview_create(panel->card);
    lv_obj_set_scrollbar_mode(panel->tile_view, LV_SCROLLBAR_MODE_OFF);
    panel->tile1 = lv_tileview_add_tile(panel->tile_view, 0, 0, LV_DIR_RIGHT);
    panel->status_label = place_label(0,0, panel->tile1, get_colors().main_font);
    lv_obj_set_width(panel->status_label, 466); 
    panel->tile2 = lv_tileview_add_tile(panel->tile_view, 1, 0, LV_DIR_LEFT);
    panel->settings_button = lv_btn_create(panel->tile2);
    lv_obj_clear_state(panel->settings_button, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(panel->settings_button, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(panel->settings_button, 1, 0);
    lv_obj_set_style_pad_all(panel->settings_button, 3, 0);
    lv_obj_align(panel->settings_button, LV_ALIGN_RIGHT_MID, -3, 0);
    panel->settings_button_label = place_label(0,0, panel->settings_button, get_colors().main_font);
    set_label_text(panel->settings_button_label, "Настройки");
    set_top_panel_theme(panel);
}

void
set_top_panel_theme(top_panel_t * panel) {
    lv_obj_set_style_bg_color(panel->card, get_colors().card_background_color, 0);
    lv_obj_set_style_border_color(panel->card, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(panel->tile_view, get_colors().header_color, 0);
    lv_obj_set_style_bg_color(panel->settings_button, get_colors().header_color, 0);
    lv_obj_set_style_border_color(panel->settings_button, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->status_label, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->settings_button_label, get_colors().header_font_color, 0);
}

lv_obj_t * 
place_label(int x_offset, int y_offset, lv_obj_t * parent, const lv_font_t * font) {
    lv_obj_t * label = lv_label_create(parent);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    set_label_text(label, "Label");
    lv_obj_set_width(label, LV_SIZE_CONTENT); 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_style_text_font(label,font,0);
    return label;
}

void
set_label_text(lv_obj_t * label, const char* msg, ...) {
    char str[50];
    va_list ap;
    va_start(ap, msg);
    vsprintf(str, msg, ap);
    va_end(ap);
    lv_label_set_text(label, str);
}

void
set_theme(int theme) {
    set_colors(theme);
    lv_obj_set_style_bg_color(main_screen, get_colors().background_color, 0);
    set_card_theme(&temperature_card);
    set_card_theme(&pressure_card);
    set_card_theme(&humidity_card);
    set_card_theme(&co2_card);
    set_datetime_card_theme(&datetime_card);
    set_top_panel_theme(&top_panel);
}

void
set_temperature(float temperature) {
    set_label_text(temperature_card.label, "%2.1f°C", (double)temperature);
}

void
set_pressure(int pressure) {
    set_label_text(pressure_card.label, "%dmm", pressure);
}

void
set_humidity(float humidity) {
    set_label_text(humidity_card.label, "%2.1f%%", (double)humidity);
}

void
set_co2(int co2) {
    set_label_text(co2_card.label, "%dppm", co2);
}

void
set_time(int hour, int minute) {
    set_label_text(datetime_card.time_label, "%d:%d", hour, minute);
}

void
set_date(int day, int month) {
    char *months[]={"%d января","%d февраля","%d марта","%d апреля","%d мая","%d июня","%d июля","%d августа","%d сентября","%d октября","%d ноября","%d декабря"};
    set_label_text(datetime_card.date_top_label, months[month-1], day);
}

void
set_day_of_week(int day_of_week) {
    char *days[]={"Понедельник", "Вторник", "Среда", "Четверг", "Пятница", "Суббота", "Воскресенье"};
    set_label_text(datetime_card.date_bottom_label, days[day_of_week-1]);
}