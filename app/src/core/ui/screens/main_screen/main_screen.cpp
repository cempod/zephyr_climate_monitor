#include "main_screen.hpp"
#include "screen_base.hpp"

#include "screen_manager.hpp"


MainScreen* MainScreen::instance = nullptr;

MainScreen& MainScreen::get() {
    static MainScreen screen;
    return screen;
}

static void screen_gesture_event(lv_event_t * e) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    switch(dir) {
        case LV_DIR_BOTTOM:
            ScreenManager::get().set_screen(ScreenType::SettingsScreen);
        break;
        default: break;
    }
}

MainScreen::MainScreen() {
    instance = this;
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(screen, screen_gesture_event, LV_EVENT_GESTURE, NULL);
}

void MainScreen::update_callbacks() {}

void MainScreen::update() {}