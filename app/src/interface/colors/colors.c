#include "colors.h"

    int current_theme = LIGHT_THEME;

    LV_FONT_DECLARE(comfortaa_16)
    LV_FONT_DECLARE(comfortaa_24)
    LV_FONT_DECLARE(comfortaa_64)

    ui_style_t light_theme = {
        .background_color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
        .on_background_color = LV_COLOR_MAKE(0xF4, 0x43, 0x36),
        .accent_color = LV_COLOR_MAKE(0xF4, 0x43, 0x36),
        .on_accent_color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
        .main_font = &comfortaa_16,
        .big_font = &comfortaa_64,
        .medium_font = &comfortaa_24
    };

    ui_style_t dark_theme = {
        .background_color = LV_COLOR_MAKE(0x28, 0x2C, 0x34),
        .on_background_color = LV_COLOR_MAKE(0xF4, 0x43, 0x36),
        .accent_color = LV_COLOR_MAKE(0xF4, 0x43, 0x36),
        .on_accent_color = LV_COLOR_MAKE(0xFF, 0xFF, 0xFF),
        .main_font = &comfortaa_16,
        .big_font = &comfortaa_64,
        .medium_font = &comfortaa_24
    };

    lv_color_t accent_colors[12] = {
        LV_COLOR_MAKE(0xB9, 0x07, 0x07),
        LV_COLOR_MAKE(0xF4, 0x43, 0x36),
        LV_COLOR_MAKE(0xFF, 0x80, 0x00),
        LV_COLOR_MAKE(0x00, 0xCC, 0x00),
        LV_COLOR_MAKE(0x00, 0xCC, 0x66),
        LV_COLOR_MAKE(0x00, 0xCC, 0xCC),
        LV_COLOR_MAKE(0x00, 0x99, 0x99),
        LV_COLOR_MAKE(0x00, 0x66, 0xCC),
        LV_COLOR_MAKE(0xCC, 0x00, 0xCC),
        LV_COLOR_MAKE(0x99, 0x00, 0x99),
        LV_COLOR_MAKE(0xCC, 0x00, 0x66),
        LV_COLOR_MAKE(0x66, 0x66, 0x66)
    };

ui_style_t 
get_colors() {
    switch (current_theme)
    {
    case LIGHT_THEME:
        return light_theme;

    case DARK_THEME:
        return dark_theme;
    
    default:
        return light_theme;
    }
}

lv_color_t 
get_accent_color(uint8_t color) {
    return accent_colors[color];
}

uint8_t
get_current_theme(void) {
    return current_theme;
}

void
set_colors(int theme) {
    current_theme = theme;
}

void
set_accent_color(uint8_t color) {
    light_theme.accent_color = accent_colors[color];
    dark_theme.accent_color = accent_colors[color];
}

