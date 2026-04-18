#include "logo_screen.hpp"
#include "screen_manager.hpp"

LogoScreen* LogoScreen::instance = nullptr;

LogoScreen& LogoScreen::get() {
    static LogoScreen screen;
    return screen;
}

static void logo_timeout(lv_timer_t * timer) {
    ScreenManager::get().set_screen(ScreenType::MainScreen);
}

LogoScreen::LogoScreen() {
    instance = this;
    screen = lv_obj_create(NULL);
    lv_obj_set_style_bg_color(screen, lv_color_make(0, 0, 0), 0);
    lv_obj_clear_flag(screen, LV_OBJ_FLAG_SCROLLABLE);

    LV_IMG_DECLARE(weather_logo);
    logo = lv_img_create(screen);
    lv_img_set_src(logo, &weather_logo);
    lv_obj_align(logo, LV_ALIGN_CENTER, 0, 0);
    lv_obj_set_size(logo, 360, 110);
}

void LogoScreen::on_show() {
    if (logo_timer == nullptr) {
        logo_timer = lv_timer_create(logo_timeout, 3000, NULL);
    }
    lv_timer_set_repeat_count(logo_timer, 1);
}

void LogoScreen::update_callbacks() {}

void LogoScreen::update() {}