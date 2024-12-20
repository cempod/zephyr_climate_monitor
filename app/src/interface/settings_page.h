#ifndef __SETTINGS_PAGE_H
#define __SETTINGS_PAGE_H

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
    lv_obj_t * parent;
    lv_obj_t * card;
    lv_obj_t * back_button;
    lv_obj_t * panel_label;
    lv_obj_t * back_button_label;
} settings_top_panel_t;

typedef struct {
    int x_size;
    int y_size;
    int x_offset;
    int y_offset;
    lv_obj_t * parent;
    lv_obj_t * card;
    lv_obj_t * tab_view;
} menu_card_t;

typedef struct {
    lv_obj_t * parent;
    lv_obj_t * label;
    lv_obj_t * day_roller;
    lv_obj_t * month_roller;
    lv_obj_t * year_roller;
    lv_obj_t * save_button;
    lv_obj_t * save_button_label;
} setup_date_page_t;

typedef struct {
    lv_obj_t * parent;
    lv_obj_t * label;
    lv_obj_t * day_roller;
    lv_obj_t * hour_roller;
    lv_obj_t * minute_roller;
    lv_obj_t * save_button;
    lv_obj_t * save_button_label;
} setup_time_page_t;


void init_settings_page(void);
void load_settings_page(void);
void set_settings_page_theme(int theme);
void update_settings_date_time(int hour, int minute, int day, int month, int year);

#endif