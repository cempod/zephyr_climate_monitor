#include "main_page.h"
#include "colors/colors.h"

#include <stdio.h>
#include <stdarg.h>


void place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card, lv_obj_t ** header, lv_obj_t ** label, lv_obj_t ** header_label);
void place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card);
void place_label(int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** label, const lv_font_t * font);
void set_label_text(lv_obj_t * label, const char* msg, ...);
void set_label_color(lv_obj_t * label, lv_color_t color);

static lv_obj_t * main_screen;
static lv_obj_t * temperature_card;
static lv_obj_t * temperature_card_header;
static lv_obj_t * pressure_card;
static lv_obj_t * pressure_card_header;
static lv_obj_t * humidity_card;
static lv_obj_t * humidity_card_header;
static lv_obj_t * co2_card;
static lv_obj_t * co2_card_header;
static lv_obj_t * time_card;
static lv_obj_t * top_panel;
static lv_obj_t * temperature_header_label;
static lv_obj_t * pressure_header_label;
static lv_obj_t * humidity_header_label;
static lv_obj_t * co2_header_label;
static lv_obj_t * time_label;
static lv_obj_t * date_label;
static lv_obj_t * week_label;
static lv_obj_t * temperature_label;
static lv_obj_t * pressure_label;
static lv_obj_t * humidity_label;
static lv_obj_t * co2_label;

void
init_main_page(void) {
    main_screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(main_screen, get_colors().background_color, 0);
    place_card(200, 150, 5, 55, &main_screen, &temperature_card, &temperature_card_header, &temperature_label, &temperature_header_label);
    set_label_text(temperature_header_label, "Температура");
    place_card(150, 100, 5, 215, &main_screen, &pressure_card, &pressure_card_header, &pressure_label, &pressure_header_label);
    set_label_text(pressure_header_label, "Давление");
    place_card(150, 100, 165, 215, &main_screen, &humidity_card, &humidity_card_header, &humidity_label, &humidity_header_label);
    set_label_text(humidity_header_label, "Влажность");
    place_card(150, 100, 325, 215, &main_screen, &co2_card, &co2_card_header, &co2_label, &co2_header_label);
    set_label_text(co2_header_label, "CO2");
    place_headless_card(260, 150, 215, 55, &main_screen, &time_card);
    place_headless_card(470, 40, 5, 5, &main_screen, &top_panel);
    lv_obj_set_style_bg_color(top_panel, get_colors().header_color, 0);
    place_label(0,0, &time_card, &time_label, get_colors().big_font);
    place_label(0,-50, &time_card, &date_label, get_colors().main_font);
    place_label(0,50, &time_card, &week_label, get_colors().main_font);
    set_label_color(time_label, get_colors().main_font_color);
    set_label_color(date_label, get_colors().main_font_color);
    set_label_color(week_label, get_colors().main_font_color);
    set_label_text(time_label, "22:44");
    set_label_text(date_label, "Декабрь 12");
    set_label_text(week_label, "Четверг");
    lv_obj_set_style_text_font(temperature_label, get_colors().big_font, 0);
    lv_obj_align(temperature_label, LV_ALIGN_CENTER, 0, 18);
    set_label_text(temperature_label, "27.3°C");
    set_label_text(pressure_label, "765mm");
    set_label_text(humidity_label, "49.8%%");
    set_label_text(co2_label, "632ppm");
}

void
load_main_page(void) {
    lv_scr_load(main_screen);
    set_theme(DARK_THEME);
}

void 
place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card, lv_obj_t ** header, lv_obj_t ** label, lv_obj_t ** header_label) {
    *card = lv_obj_create(*parent);
    lv_obj_set_style_bg_color(*card, get_colors().card_background_color, 0);
    lv_obj_align(*card, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    lv_obj_set_size(*card, x_size, y_size);
    lv_obj_set_style_pad_all(*card,0,0);
    lv_obj_set_style_border_color(*card, get_colors().border_color, 0);
    *header = lv_obj_create(*card);
    lv_obj_set_style_bg_color(*header, get_colors().header_color, 0);
    lv_obj_set_size(*header, x_size-4, 35);
    lv_obj_align(*header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_side(*header, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_radius(*header, 0, 0);
    lv_obj_set_style_pad_all(*header,0,0);
    lv_obj_set_style_bg_color (*header , get_colors().header_color, 0);
    place_label(0,0, header, header_label, get_colors().main_font);
    place_label(0,21, card, label, get_colors().medium_font);
    set_label_color(*label, get_colors().main_font_color);
}

void 
place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card) {
    *card = lv_obj_create(*parent);
    lv_obj_set_style_bg_color(*card, get_colors().card_background_color, 0);
    lv_obj_set_style_border_color(*card, get_colors().border_color, 0);
    lv_obj_align(*card, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    lv_obj_set_size(*card, x_size, y_size);
    lv_obj_set_style_pad_all(*card,0,0);
}

void 
place_label(int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** label, const lv_font_t * font) {
    *label = lv_label_create(*parent);
    lv_label_set_long_mode(*label, LV_LABEL_LONG_WRAP);
    set_label_text(*label, "Label");
    lv_obj_set_width(*label, LV_SIZE_CONTENT); 
    lv_obj_set_style_text_align(*label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(*label, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_style_text_font(*label,font,0);
    lv_obj_set_style_text_color(*label, get_colors().header_font_color, 0);
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
set_label_color(lv_obj_t * label, lv_color_t color) {
    lv_obj_set_style_text_color(label, color, 0);
}

void
set_theme(int theme) {
    set_colors(theme);
    lv_obj_set_style_bg_color(main_screen, get_colors().background_color, 0);
    lv_obj_set_style_bg_color(temperature_card, get_colors().card_background_color, 0);
    lv_obj_set_style_bg_color(pressure_card, get_colors().card_background_color, 0);
    lv_obj_set_style_bg_color(humidity_card, get_colors().card_background_color, 0);
    lv_obj_set_style_bg_color(co2_card, get_colors().card_background_color, 0);
    lv_obj_set_style_bg_color(time_card, get_colors().card_background_color, 0);
    lv_obj_set_style_bg_color(temperature_card_header, get_colors().header_color, 0);
    lv_obj_set_style_bg_color(pressure_card_header, get_colors().header_color, 0);
    lv_obj_set_style_bg_color(humidity_card_header, get_colors().header_color, 0);
    lv_obj_set_style_bg_color(co2_card_header, get_colors().header_color, 0);
    lv_obj_set_style_bg_color(top_panel, get_colors().header_color, 0);
    set_label_color(temperature_header_label, get_colors().header_font_color);
    set_label_color(pressure_header_label, get_colors().header_font_color);
    set_label_color(humidity_header_label, get_colors().header_font_color);
    set_label_color(time_label, get_colors().main_font_color);
    set_label_color(date_label, get_colors().main_font_color);
    set_label_color(week_label, get_colors().main_font_color);
    set_label_color(temperature_label, get_colors().main_font_color);
    set_label_color(pressure_label, get_colors().main_font_color);
    set_label_color(humidity_label, get_colors().main_font_color);
    set_label_color(co2_label, get_colors().main_font_color);
    lv_obj_set_style_border_color(temperature_card, get_colors().border_color, 0);
    lv_obj_set_style_border_color(pressure_card, get_colors().border_color, 0);
    lv_obj_set_style_border_color(humidity_card, get_colors().border_color, 0);
    lv_obj_set_style_border_color(co2_card, get_colors().border_color, 0);
    lv_obj_set_style_border_color(time_card, get_colors().border_color, 0);
    lv_obj_set_style_border_color(top_panel, get_colors().border_color, 0);
}