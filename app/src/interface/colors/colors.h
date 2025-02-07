#ifndef __COLORS_H
#define __COLORS_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

enum Themes {
    LIGHT_THEME = 0,
    DARK_THEME
};

typedef struct {
    lv_color_t accent_color;
    lv_color_t on_accent_color;
    lv_color_t background_color;
    lv_color_t on_background_color;
    const lv_font_t * main_font;
    const lv_font_t * big_font;
    const lv_font_t * medium_font;
} ui_style_t;

ui_style_t get_colors();
void set_colors(int theme);

#endif