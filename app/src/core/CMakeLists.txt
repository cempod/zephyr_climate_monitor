cmake_minimum_required(VERSION 3.20)

set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/system/backlight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/system/event_machine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/system/param_machine.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/ui.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/screen_manager.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/main_screen/main_screen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/settings/settings_screen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/logo/logo_screen.cpp
    ${CMAKE_CURRENT_LIST_DIR}/ui/icons/weather_logo.c
)

add_library(core INTERFACE)

target_include_directories(core INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
    ${CMAKE_CURRENT_LIST_DIR}/system
    ${CMAKE_CURRENT_LIST_DIR}/ui
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/main_screen
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/settings
    ${CMAKE_CURRENT_LIST_DIR}/ui/screens/logo
)

target_sources(core INTERFACE ${SRCS})