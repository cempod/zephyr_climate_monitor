# SPDX-License-Identifier: Apache-2.0

cmake_minimum_required(VERSION 3.20.0)
find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})
project(THWM)

add_compile_definitions(LV_LVGL_H_INCLUDE_SIMPLE)

target_sources(app PRIVATE src/main.c)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/src/core)

target_link_libraries(app PRIVATE
    core
)