#include "backlight.h"

#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/pwm.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(BACKLIGHT);

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

void backlight_thread(void *p1, void *p2, void *p3) {
    static const struct pwm_dt_spec display_backlight = PWM_DT_SPEC_GET(DISPLAY_LED_NODE);
    if (pwm_is_ready_dt(&display_backlight)) {
        pwm_set_pulse_dt(&display_backlight, display_backlight.period*99/100);
    }
    while(1) {
        k_msleep(1000);
    }
}