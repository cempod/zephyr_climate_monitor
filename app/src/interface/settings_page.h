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


void init_settings_page(void);
void load_settings_page(void);
void set_settings_page_theme(int theme);

#endif