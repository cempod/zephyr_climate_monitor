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

enum AccentColors {
    ACCENT_RED_DARK = 0,
    ACCENT_RED,
    ACCENT_ORANGE,
    ACCENT_GREEN,
    ACCENT_GREEN_SOFT,
    ACCENT_CYAN,
    ACCENT_CYAN_DARK,
    ACCENT_BLUE,
    ACCENT_PURPLE,
    ACCENT_PURPLE_DARK,
    ACCENT_MAGENTA,
    ACCENT_GREY
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
lv_color_t get_accent_color(uint8_t color);
uint8_t get_current_theme(void);
void set_colors(int theme);
void set_accent_color(uint8_t color);

#endif