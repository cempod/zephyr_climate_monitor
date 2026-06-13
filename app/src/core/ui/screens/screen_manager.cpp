#include "screen_manager.hpp"
#include "logo_screen.hpp"
#include "param_machine.hpp"
#include "screen_base.hpp"
#include "param_machine.hpp"

ScreenManager& ScreenManager::get() {
    static ScreenManager manager;
    return manager;
}

ScreenManager::ScreenManager() {
    auto &pm = ParamMachine::get_machine();
    if (pm.get_startup_logo()) {
        current_screen = &LogoScreen::get();
    } else {
        current_screen = &MainScreen::get();
    }
    current_screen->show();
}

void ScreenManager::set_screen(ScreenType type) {
    ScreenBase* new_screen;
    switch(type) {
        case ScreenType::MainScreen: {
            new_screen = &MainScreen::get();
            break;
        }
        case ScreenType::SettingsScreen: {
            new_screen = &SettingsScreen::get();
            break;
        }
        case ScreenType::WifiScreen: {
            new_screen = &WifiScreen::get();
            break;
        }
        default: return;
    }
    new_screen->show();
    current_screen->detach();
    current_screen = new_screen;
}