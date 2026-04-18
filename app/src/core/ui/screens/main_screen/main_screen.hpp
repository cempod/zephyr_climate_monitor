#pragma once

#include "event_machine.hpp"
#include "screen_base.hpp"

class MainScreen : public ScreenBase {
    public:
        static MainScreen& get();
        void update_callbacks() override;
        void update() override;
    private:
        MainScreen();
        static MainScreen* instance;
        
        virtual ~MainScreen() = default;
        
};