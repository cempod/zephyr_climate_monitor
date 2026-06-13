#pragma once

#include <lvgl.h>

class StyleManager {
    public:
        static StyleManager& get();

        lv_style_t * get_button_style(void) {return &button_style;}

        StyleManager(const StyleManager&) = delete;
        StyleManager& operator=(const StyleManager&) = delete;
    private:
        StyleManager();

        lv_style_t button_style;
};