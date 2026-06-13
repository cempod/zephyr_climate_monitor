#pragma once

#include "screen_base.hpp"
#include "main_screen.hpp"
#include "settings_screen.hpp"
#include "wifi_screen.hpp"

enum class ScreenType { MainScreen, SettingsScreen, WifiScreen };

class ScreenManager {
    public:
        static ScreenManager& get();

        void update(){
            if (current_screen) current_screen->update();
        }

        void set_screen(ScreenType type);
    private:
        ScreenManager();

        ScreenBase* current_screen = nullptr;
};