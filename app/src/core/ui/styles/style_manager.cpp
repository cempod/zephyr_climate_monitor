#include "style_manager.hpp"

StyleManager& StyleManager::get() {
    static StyleManager manager;
    return manager;
}

StyleManager::StyleManager() {
    lv_style_init(&button_style);
    lv_style_set_radius(&button_style, 0);
}