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
#include <zephyr/usb/usb_device.h>
#include <zephyr/usb/usbd.h>
#include <zephyr/drivers/uart.h>
#include <zephyr/sys/ring_buffer.h>

const struct device *const uart_dev = DEVICE_DT_GET_ONE(zephyr_cdc_acm_uart);

#define RING_BUF_SIZE 1024
uint8_t ring_buffer[RING_BUF_SIZE];

struct ring_buf ringbuf;

static bool rx_throttled;

lv_obj_t *console_label;

#define LOG_LEVEL CONFIG_LOG_DEFAULT_LEVEL
#include <zephyr/logging/log.h>
LOG_MODULE_REGISTER(app);

#define DISPLAY_LED_NODE DT_ALIAS(backlight0)

static const struct gpio_dt_spec display_led = GPIO_DT_SPEC_GET(DISPLAY_LED_NODE, gpios);

struct data_item_type {
    uint8_t str[64];
};

char console_msgq_buffer[10 * sizeof(struct data_item_type)];
struct k_msgq console_msgq;



static void interrupt_handler(const struct device *dev, void *user_data)
{
	ARG_UNUSED(user_data);

	while (uart_irq_update(dev) && uart_irq_is_pending(dev)) {
		if (!rx_throttled && uart_irq_rx_ready(dev)) {
			int recv_len, rb_len;
			uint8_t buffer[64];
			size_t len = MIN(ring_buf_space_get(&ringbuf),
					 sizeof(buffer));

			if (len == 0) {
				/* Throttle because ring buffer is full */
				uart_irq_rx_disable(dev);
				rx_throttled = true;
				continue;
			}

			recv_len = uart_fifo_read(dev, buffer, len);
			if (recv_len < 0) {
				LOG_ERR("Failed to read UART FIFO");
				recv_len = 0;
			};

			rb_len = ring_buf_put(&ringbuf, buffer, recv_len);
			if (rb_len < recv_len) {
				LOG_ERR("Drop %u bytes", recv_len - rb_len);
			}

			LOG_DBG("tty fifo -> ringbuf %d bytes", rb_len);
			if (rb_len) {
				uart_irq_tx_enable(dev);
			}
		}

		if (uart_irq_tx_ready(dev)) {
			uint8_t buffer[64];
			int rb_len, send_len;

			rb_len = ring_buf_get(&ringbuf, buffer, sizeof(buffer));
			if (!rb_len) {
				LOG_DBG("Ring buffer empty, disable TX IRQ");
				uart_irq_tx_disable(dev);
				continue;
			}

			if (rx_throttled) {
				uart_irq_rx_enable(dev);
				rx_throttled = false;
			}

			send_len = uart_fifo_fill(dev, buffer, rb_len);
			if (send_len < rb_len) {
				LOG_ERR("Drop %d bytes", rb_len - send_len);
			}

			//lv_label_ins_text(console_label, LV_LABEL_POS_LAST, (char*)buffer);
			struct data_item_type data;
			memcpy(data.str, buffer, sizeof(buffer));
			k_msgq_put(&console_msgq, &data, K_NO_WAIT);

			LOG_DBG("ringbuf -> tty fifo %d bytes", send_len);
		}
	}
}

int main(void)
{
	k_msgq_init(&console_msgq, console_msgq_buffer, sizeof(struct data_item_type), 10);
	if (!gpio_is_ready_dt(&display_led)) {
		return 0;
	}
	int ret = gpio_pin_configure_dt(&display_led, GPIO_OUTPUT_ACTIVE);
	if (ret < 0) {
		return 0;
	}
	ret = gpio_pin_set_dt(&display_led, 1);
		if (ret < 0) {
			return 0;
		}

	ret = usb_enable(NULL);

	if (ret != 0) {
		LOG_ERR("Failed to enable USB");
		return 0;
	}

	ring_buf_init(&ringbuf, sizeof(ring_buffer), ring_buffer);

	while (true) {
		uint32_t dtr = 0U;

		uart_line_ctrl_get(uart_dev, UART_LINE_CTRL_DTR, &dtr);
		if (dtr) {
			break;
		} else {
			/* Give CPU resources to low priority threads. */
			k_sleep(K_MSEC(100));
		}
	}

	ret = uart_line_ctrl_set(uart_dev, UART_LINE_CTRL_DCD, 1);
	if (ret) {
		LOG_WRN("Failed to set DCD, ret code %d", ret);
	}

	ret = uart_line_ctrl_set(uart_dev, UART_LINE_CTRL_DSR, 1);
	if (ret) {
		LOG_WRN("Failed to set DSR, ret code %d", ret);
	}

	/* Wait 100ms for the host to do all settings */
	k_msleep(100);

	uart_irq_callback_set(uart_dev, interrupt_handler);

	/* Enable rx interrupts */
	uart_irq_rx_enable(uart_dev);
	const struct device *display_dev;

	display_dev = DEVICE_DT_GET(DT_CHOSEN(zephyr_display));
	if (!device_is_ready(display_dev)) {
		LOG_ERR("Device not ready, aborting test");
		return 0;
	}

	console_label = lv_label_create(lv_scr_act());

	lv_label_set_text(console_label, "");
	lv_obj_align(console_label, LV_ALIGN_OUT_TOP_MID, 0, 0);
	lv_obj_set_width(console_label, 480);
	//lv_obj_set_height(console_label, 320);
	lv_label_set_long_mode(console_label, LV_LABEL_LONG_WRAP); 

	lv_task_handler();
	display_blanking_off(display_dev);


	while (1) {
		struct data_item_type data;
		while(k_msgq_get(&console_msgq, &data, K_NO_WAIT) == 0) {
			lv_label_ins_text(console_label, LV_LABEL_POS_LAST, (char*)data.str);
		}
		lv_task_handler();
		k_sleep(K_USEC(1));
	}
}
