/*
 * Copyright (c) 2018 Jan Van Winkel <jan.van_winkel@dxplore.eu>
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <zephyr/drivers/gpio.h>
#include <lvgl.h>
#include <stdio.h>
#include <string.h>
#include <zephyr/kernel.h>
#include <lvgl_input_device.h>
#include <zephyr/drivers/gpio.h>
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

static const struct gpio_dt_spec display_led = GPIO_DT_SPEC_GET(DISPLAY_LED_NODE, gpios);

int main(void)
{
	if (!gpio_is_ready_dt(&display_led)) {
		return 0;
	}
	int ret = gpio_pin_configure_dt(&display_led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}

	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting");
		return 0;
	}

	lv_task_handler();
	display_blanking_off(display_dev);

	ret = gpio_pin_set_dt(&display_led, 1);
		if (ret < 0) {
			return 0;
		}

	while (1) {
		lv_task_handler();
		k_sleep(K_MSEC(10));
	}
}
