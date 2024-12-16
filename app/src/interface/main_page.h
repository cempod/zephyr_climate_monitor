#ifndef __MAIN_PAGE_H
#define __MAIN_PAGE_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

typedef struct {
    int x_size;
    int y_size;
    int x_offset;
    int y_offset;
    const char* header_string;
    lv_obj_t * parent;
    lv_obj_t * card;
    lv_obj_t * header;
    lv_obj_t * label;
    lv_obj_t * header_label;
} card_t;

typedef struct {
    int x_size;
    int y_size;
    int x_offset;
    int y_offset;
    lv_obj_t * parent;
    lv_obj_t * card;
    lv_obj_t * date_top_label;
    lv_obj_t * date_bottom_label;
    lv_obj_t * time_label;
} datetime_card_t;

typedef struct {
    int x_size;
    int y_size;
    int x_offset;
    int y_offset;
    lv_obj_t * parent;
    lv_obj_t * card;
    lv_obj_t * tile_view;
    lv_obj_t * tile1;
    lv_obj_t * tile2;
    lv_obj_t * settings_button;
    lv_obj_t * status_label;
    lv_obj_t * settings_button_label;
} top_panel_t;

void init_main_page(void);
void load_main_page(void);
void set_theme(int theme);

void set_temperature(float temperature);
void set_pressure(int pressure);
void set_humidity(float humidity);
void set_co2(int co2);
void set_time(int hour, int minute);
void set_date(int day, int month);
void set_day_of_week(int day_of_week);

#endif