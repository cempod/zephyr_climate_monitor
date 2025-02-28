#include "backlight.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

static const struct pwm_dt_spec display_backlight = PWM_DT_SPEC_GET(DISPLAY_LED_NODE);

void
backlight_task() {
    set_brightness(100);

    while(1) {
        k_sleep(K_MSEC(1000));
    }

}

void
set_brightness(uint8_t brightness) {
    if (pwm_is_ready_dt(&display_backlight)) {
        pwm_set_pulse_dt(&display_backlight, display_backlight.period*brightness/100);
    }
}


K_THREAD_DEFINE(backlight_task0, 1024, backlight_task, NULL, NULL, NULL,
		7, 0, 0);