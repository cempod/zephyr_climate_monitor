#include "backlight.h"

#include <sys/_stdint.h>
#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

#include "event_machine.hpp"

LOG_MODULE_REGISTER(BACKLIGHT);

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

#define MIN_PCT 10
#define MAX_PCT 99

static int target_brightness = 0;

static void change_backlight(sys_event_s event) {
    target_brightness = event.payload.int_p < MIN_PCT ? MIN_PCT : (event.payload.int_p > MAX_PCT ? MAX_PCT : event.payload.int_p);
}

void backlight_thread(void *p1, void *p2, void *p3) {
    static const struct pwm_dt_spec display_backlight = PWM_DT_SPEC_GET(DISPLAY_LED_NODE);
    static int current_brightness = 0;
    int step = 1;
    EventMachine em = EventMachine::get_machine();
    em.register_callback(EV_BACKLIGHT, change_backlight);
    sys_event_s backlight_event = {
        .event_type = EV_BACKLIGHT,
        .payload { .int_p = 100 }
    };
    em.call(backlight_event);
    while(1) {
        if (target_brightness != current_brightness) {
            if (target_brightness > current_brightness) {
                if (target_brightness - current_brightness >= step) {
                    current_brightness += step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            if (target_brightness < current_brightness) {
                if (current_brightness - target_brightness >= step) {
                    current_brightness -= step;
                } else {
                    current_brightness = target_brightness;
                }
            }
            if (pwm_is_ready_dt(&display_backlight)) {
                pwm_set_pulse_dt(&display_backlight, display_backlight.period*current_brightness/100);
            }
        }
        k_msleep(20);
    }
}