#include <zephyr/kernel.h>
#include <zephyr/logging/log.h>

#include "backlight.h"

LOG_MODULE_REGISTER(MAIN);

k_tid_t backlight_tid;
K_THREAD_STACK_DEFINE(backlight_thread_stack_area, 1024);
struct k_thread backlight_thread_data;

int main(void)
{	
	LOG_INF("Starting threads");

	backlight_tid = k_thread_create(&backlight_thread_data,
								backlight_thread_stack_area,
								K_THREAD_STACK_SIZEOF(backlight_thread_stack_area),
								backlight_thread,
								NULL, NULL, NULL,
								5, 0, K_NO_WAIT);
	LOG_INF("Created backlight thread");

	LOG_INF("Aborting from main");

	return 0;
}
