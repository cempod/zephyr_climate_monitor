# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(THWM)

add_compile_definitions(LV_LVGL_H_INCLUDE_SIMPLE)

target_sources(app PRIVATE src/main.c)

target_sources(app PRIVATE
${CMAKE_CURRENT_LIST_DIR}/src/core/system/backlight.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/system/event_machine.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/system/param_machine.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/ui.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/styles/style_manager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/screen_manager.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/main_screen/main_screen.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/settings/settings_screen.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/settings/wifi_screen/wifi_screen.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/logo/logo_screen.cpp
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/icons/weather_logo.c
)

target_include_directories(app PRIVATE
${CMAKE_CURRENT_LIST_DIR}/src/core
${CMAKE_CURRENT_LIST_DIR}/src/core/system
${CMAKE_CURRENT_LIST_DIR}/src/core/ui
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/styles
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/main_screen
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/settings
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/settings/wifi_screen
${CMAKE_CURRENT_LIST_DIR}/src/core/ui/screens/logo
)