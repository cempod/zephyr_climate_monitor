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
#include <zephyr/logging/log.h>
#include <zephyr/drivers/rtc.h>
#include <zephyr/sys/util.h>

#include "main_page.h"
#include "settings_page.h"
#include "colors.h"
#include "func.h"
LOG_MODULE_REGISTER(app);

const struct device *const rtc = DEVICE_DT_GET(DT_ALIAS(rtc));



static int get_date_time(const struct device *rtc)
{
	int ret = 0;
	struct rtc_time tm;

	ret = rtc_get_time(rtc, &tm);
	if (ret < 0) {
		return ret;
	}

	update_date_time(tm.tm_hour, tm.tm_min, tm.tm_mday, tm.tm_mon+1, tm.tm_year+1900, tm.tm_wday+1);

	return ret;
}

int main(void)
{	
	if (!device_is_ready(rtc)) {
		return 0;
	}



	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting");
		return 0;
	}
	init_interface();
	//set_theme(DARK_THEME);

	load_main_page();

	lv_task_handler();
	display_blanking_off(display_dev);

	while (1) {
		get_date_time(rtc);
		lv_task_handler();
		k_sleep(K_MSEC(10));
	}
}
