#include "settings_screen.hpp"
#include "param_machine.hpp"
#include "screen_manager.hpp"
#include "event_machine.hpp"

SettingsScreen* SettingsScreen::instance = nullptr;

SettingsScreen& SettingsScreen::get() {
    static SettingsScreen screen;
    return screen;
}

static void screen_gesture_event(lv_event_t * e) {
    lv_dir_t dir = lv_indev_get_gesture_dir(lv_indev_get_act());
    switch(dir) {
        case LV_DIR_TOP:
            ScreenManager::get().set_screen(ScreenType::MainScreen);
        break;
        default: break;
    }
}

static void slider_event_cb(lv_event_t * e)
{
    lv_obj_t * slider = lv_event_get_target_obj(e);
    EventMachine::get_machine().call({.event_type = EV_BACKLIGHT,
                .payload = { .int_p = lv_slider_get_value(slider)}});
    ParamMachine::get_machine().set_brightness(lv_slider_get_value(slider));
}

SettingsScreen::SettingsScreen() {
    instance = this;
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_add_event_cb(screen, screen_gesture_event, LV_EVENT_GESTURE, NULL);

    brightness_slider = lv_slider_create(screen);
    lv_obj_align(brightness_slider, LV_ALIGN_TOP_MID, 0, 50);
    lv_slider_set_range(brightness_slider, 10, 100);
    lv_slider_set_value(brightness_slider, ParamMachine::get_machine().get_brightness(), LV_ANIM_OFF);
    lv_obj_add_event_cb(brightness_slider, slider_event_cb, LV_EVENT_VALUE_CHANGED, NULL);
}

void SettingsScreen::update_callbacks() {}

void SettingsScreen::update() {}