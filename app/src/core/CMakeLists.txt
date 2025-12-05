cmake_minimum_required(VERSION 3.20)

set(SRCS
    ${CMAKE_CURRENT_LIST_DIR}/backlight.cpp
    ${CMAKE_CURRENT_LIST_DIR}/event_machine.cpp
)

add_library(core INTERFACE)

target_include_directories(core INTERFACE
    ${CMAKE_CURRENT_LIST_DIR}
)

target_sources(core INTERFACE ${SRCS})