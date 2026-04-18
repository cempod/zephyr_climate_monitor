#include "ui.h"
#include "screen_manager.hpp"
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/drivers/display.h>
#include <lvgl.h>
#include <zephyr/kernel.h>
#include <lvgl_input_device.h>
#include <zephyr/logging/log.h>

LOG_MODULE_REGISTER(UI);

void ui_thread(void *p1, void *p2, void *p3) {

    const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting");
		return;
	}

	ScreenManager& sm = ScreenManager::get();

    while (1) {
		sm.update();
		lv_task_handler();
		k_sleep(K_MSEC(10));
	}

}