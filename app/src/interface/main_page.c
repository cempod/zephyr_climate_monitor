#include "main_page.h"

#include <stdio.h>
#include <stdarg.h>


void place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card, lv_obj_t ** header, lv_obj_t ** header_label);
void place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card);
void place_label(int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** label, const lv_font_t * font);
void set_label_text(lv_obj_t * label, const char* msg, ...);

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

void
init_main_page(void) {
    main_screen = lv_obj_create(NULL);
    place_card(150, 150, 5, 55, &main_screen, &temperature_card, &temperature_card_header, &temperature_header_label);
    set_label_text(temperature_header_label, "Temperature");
    place_card(150, 100, 5, 215, &main_screen, &pressure_card, &pressure_card_header, &pressure_header_label);
    set_label_text(pressure_header_label, "Pressure");
    place_card(150, 100, 165, 215, &main_screen, &humidity_card, &humidity_card_header, &humidity_header_label);
    set_label_text(humidity_header_label, "Humidity");
    place_card(150, 100, 325, 215, &main_screen, &co2_card, &co2_card_header, &co2_header_label);
    set_label_text(co2_header_label, "CO2");
    place_headless_card(310, 150, 165, 55, &main_screen, &time_card);
    place_headless_card(470, 40, 5, 5, &main_screen, &top_panel);
}

void
load_main_page(void) {
    lv_scr_load(main_screen);
}

void 
place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card, lv_obj_t ** header, lv_obj_t ** header_label) {
    *card = lv_obj_create(*parent);
    lv_obj_align(*card, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    lv_obj_set_size(*card, x_size, y_size);
    lv_obj_set_style_pad_all(*card,0,0);
    *header = lv_obj_create(*card);
    lv_obj_set_size(*header, x_size-4, 35);
    lv_obj_align(*header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_side(*header, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_radius(*header, 0, 0);
    lv_obj_set_style_pad_all(*header,0,0);
    lv_obj_set_style_bg_color (*header , lv_color_make(255,51,51), 0);
    place_label(0,0, header, header_label, &lv_font_montserrat_14);
}

void 
place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t ** parent, lv_obj_t ** card) {
    *card = lv_obj_create(*parent);
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
    lv_obj_set_style_text_color(*label, lv_color_make(255,255,255), 0);
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