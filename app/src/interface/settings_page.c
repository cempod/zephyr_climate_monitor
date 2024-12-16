#include "settings_page.h"
#include "colors/colors.h"
#include "func.h"

void place_settings_top_panel(settings_top_panel_t * panel, lv_obj_t * parent);
void set_settings_top_panel_theme(settings_top_panel_t * panel);

static lv_obj_t * settings_screen;

static settings_top_panel_t settings_top_panel = {
    .x_size = 470,
    .y_size = 40,
    .x_offset = 5,
    .y_offset = 5,
};

void
init_settings_page() {
    settings_screen = lv_obj_create(NULL);
    place_settings_top_panel(&settings_top_panel, settings_screen);
}

void
load_settings_page() {
    lv_scr_load(settings_screen);
}

void
set_settings_page_theme(int theme) {
    lv_obj_set_style_bg_color(settings_screen, get_colors().background_color, 0);
    set_settings_top_panel_theme(&settings_top_panel);
}

static void back_button_event_handler(lv_event_t * e)
{
    lv_event_code_t code = lv_event_get_code(e);

    if(code == LV_EVENT_CLICKED) {
        load_main_page();
    }
}

void 
place_settings_top_panel(settings_top_panel_t * panel, lv_obj_t * parent) {
    panel->card = lv_obj_create(parent);
    lv_obj_align(panel->card, LV_ALIGN_TOP_LEFT, panel->x_offset, panel->y_offset);
    lv_obj_set_size(panel->card, panel->x_size, panel->y_size);
    lv_obj_set_style_pad_all(panel->card,0,0);
    panel->panel_label = place_label(0,0, panel->card, get_colors().main_font);
    panel->back_button = lv_btn_create(panel->card);
    lv_obj_clear_state(panel->back_button, LV_STATE_FOCUS_KEY);
    lv_obj_set_style_shadow_opa(panel->back_button, LV_OPA_TRANSP, 0);
    lv_obj_set_style_border_width(panel->back_button, 1, 0);
    lv_obj_set_style_pad_all(panel->back_button, 3, 0);
    lv_obj_align(panel->back_button, LV_ALIGN_RIGHT_MID, -3, 0);
    panel->back_button_label = place_label(0,0, panel->back_button, get_colors().main_font);
    set_label_text(panel->back_button_label, "Назад");
    set_label_text(panel->panel_label, "Настройки");
    set_settings_top_panel_theme(panel);
    lv_obj_add_event_cb(panel->back_button, back_button_event_handler, LV_EVENT_CLICKED, NULL);
}

void
set_settings_top_panel_theme(settings_top_panel_t * panel) {
    lv_obj_set_style_bg_color(panel->card, get_colors().header_color, 0);
    lv_obj_set_style_border_color(panel->card, get_colors().border_color, 0);
    lv_obj_set_style_bg_color(panel->back_button, get_colors().header_color, 0);
    lv_obj_set_style_border_color(panel->back_button, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->panel_label, get_colors().header_font_color, 0);
    lv_obj_set_style_text_color(panel->back_button_label, get_colors().header_font_color, 0);
}