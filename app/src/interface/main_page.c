#include "main_page.h"

static void place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t * parrent, lv_obj_t * card, lv_obj_t * header);
static void place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t * parrent, lv_obj_t * card);

lv_obj_t * main_screen;
lv_obj_t * temperature_card;
lv_obj_t * temperature_card_header;
lv_obj_t * pressure_card;
lv_obj_t * pressure_card_header;
lv_obj_t * humidity_card;
lv_obj_t * humidity_card_header;
lv_obj_t * co2_card;
lv_obj_t * co2_card_header;
lv_obj_t * time_card;
lv_obj_t * top_panel;

void
init_main_page(void) {
    main_screen = lv_obj_create(NULL);
    place_card(150, 150, 5, 55, main_screen, temperature_card, temperature_card_header);
    place_card(150, 100, 5, 215, main_screen, pressure_card, pressure_card_header);
    place_card(150, 100, 165, 215, main_screen, humidity_card, humidity_card_header);
    place_card(150, 100, 325, 215, main_screen, co2_card, co2_card_header);
    place_headless_card(310, 150, 165, 55, main_screen, time_card);
    place_headless_card(470, 40, 5, 5, main_screen, top_panel);
}

void
load_main_page(void) {
    lv_scr_load(main_screen);
}

static void 
place_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t * parrent, lv_obj_t * card, lv_obj_t * header) {
    card = lv_obj_create(parrent);
    lv_obj_align(card, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    lv_obj_set_size(card, x_size, y_size);
    lv_obj_set_style_pad_all(card,0,0);
    header = lv_obj_create(card);
    lv_obj_set_size(header, x_size-4, 35);
    lv_obj_align(header, LV_ALIGN_TOP_MID, 0, 0);
    lv_obj_set_style_border_side(header, LV_BORDER_SIDE_NONE, 0);
    lv_obj_set_style_radius(header, 0, 0);
    lv_obj_set_style_pad_all(header,0,0);
    lv_obj_set_style_bg_color (header , lv_color_make(120,120,120), 0);
}

static void 
place_headless_card(int x_size, int y_size, int x_offset, int y_offset, lv_obj_t * parrent, lv_obj_t * card) {
    card = lv_obj_create(parrent);
    lv_obj_align(card, LV_ALIGN_TOP_LEFT, x_offset, y_offset);
    lv_obj_set_size(card, x_size, y_size);
    lv_obj_set_style_pad_all(card,0,0);
}