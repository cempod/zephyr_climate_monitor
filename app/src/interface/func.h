#ifndef __FUNC_PAGE_H
#define __FUNC_PAGE_H

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#include <stdio.h>
#include <stdarg.h>
#include "colors/colors.h"
#include "main_page.h"
#include "settings_page.h"

static inline void
init_interface(void) {
    init_main_page();
    init_settings_page();
}

static inline void
set_theme(int theme) {
    set_colors(theme);
    set_main_page_theme(theme);
    set_settings_page_theme(theme);
}

static inline void
update_date_time(int hour, int minute, int day, int month, int year, int day_of_week) {
    set_time(hour, minute);
	set_date(day, month);
	set_day_of_week(day_of_week);
	update_settings_date_time(hour, minute, day, month, year);
}

static inline void
set_label_text(lv_obj_t * label, const char* msg, ...) {
    char str[50];
    va_list ap;
    va_start(ap, msg);
    vsprintf(str, msg, ap);
    va_end(ap);
    lv_label_set_text(label, str);
}

static inline lv_obj_t * 
place_label(int x_offset, int y_offset, lv_obj_t * parent, const lv_font_t * font) {
    lv_obj_t * label = lv_label_create(parent);
    lv_label_set_long_mode(label, LV_LABEL_LONG_WRAP);
    set_label_text(label, "Label");
    lv_obj_set_width(label, LV_SIZE_CONTENT); 
    lv_obj_set_style_text_align(label, LV_TEXT_ALIGN_CENTER, 0);
    lv_obj_align(label, LV_ALIGN_CENTER, x_offset, y_offset);
    lv_obj_set_style_text_font(label,font,0);
    return label;
}

#endif