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
#include <zephyr/drivers/rtc.h>
#include <zephyr/sys/util.h>

#include "main_page.h"
LOG_MODULE_REGISTER(app);

const struct device *const rtc = DEVICE_DT_GET(DT_ALIAS(rtc));

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

static const struct gpio_dt_spec display_led = GPIO_DT_SPEC_GET(DISPLAY_LED_NODE, gpios);

static int set_date_time(const struct device *rtc)
{
	int ret = 0;
	struct rtc_time tm = {
		.tm_year = 2024 - 1900,
		.tm_mon = 12 - 1,
		.tm_mday = 16,
		.tm_hour = 15,
		.tm_min = 55,
		.tm_sec = 0,
	};

	ret = rtc_set_time(rtc, &tm);
	if (ret < 0) {
		return ret;
	}
	return ret;
}

static int get_date_time(const struct device *rtc)
{
	int ret = 0;
	struct rtc_time tm;

	ret = rtc_get_time(rtc, &tm);
	if (ret < 0) {
		return ret;
	}

	set_time(tm.tm_hour, tm.tm_min);
	set_date(tm.tm_mday, tm.tm_mon);

	return ret;
}

int main(void)
{	
	if (!device_is_ready(rtc)) {
		return 0;
	}

	set_date_time(rtc);

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
	init_main_page();
	load_main_page();

	lv_task_handler();
	display_blanking_off(display_dev);

	ret = gpio_pin_set_dt(&display_led, 1);
		if (ret < 0) {
			return 0;
		}

	while (1) {
		get_date_time(rtc);
		lv_task_handler();
		k_sleep(K_MSEC(10));
	}
}
