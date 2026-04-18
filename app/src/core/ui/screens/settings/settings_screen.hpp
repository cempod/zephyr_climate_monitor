#pragma once

#include "screen_base.hpp"

class SettingsScreen : public ScreenBase {
    public:
        static SettingsScreen& get();
        void update_callbacks() override;
        void update() override;
    private:
        SettingsScreen();
        static SettingsScreen* instance;
        
        virtual ~SettingsScreen() = default;

        lv_obj_t * brightness_slider;
};