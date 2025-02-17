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

void
set_colors(int theme) {
    current_theme = theme;
}

