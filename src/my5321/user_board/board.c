/*
 * Copyright (c) 2026
 * Board init for HPM5321 isolated USB-CAN FD adapter (based on hpm5300evk).
 */

#include "board.h"
#include "hpm_gpio_drv.h"
#include "hpm_uart_drv.h"

/* 板级资源初始化：时钟、引脚已在 pinmux.c 完成，这里放板级外设使能 */
void board_init(void)
{
    /* 调用 SDK 通用板级初始化（clock/pinmux/console） */
    board_init_clock();
    board_init_pinmux();
    board_init_console();
}

void board_init_led_pins(void)
{
    gpio_set_pin_output(BOARD_LED_GPIO_BASE, BOARD_LED_GPIO_PIN);
}

void board_led_toggle(void)
{
    gpio_toggle_pin(BOARD_LED_GPIO_BASE, BOARD_LED_GPIO_PIN);
}

void board_led_on(void)
{
    gpio_write_pin(BOARD_LED_GPIO_BASE, BOARD_LED_GPIO_PIN, 0);
}

void board_led_off(void)
{
    gpio_write_pin(BOARD_LED_GPIO_BASE, BOARD_LED_GPIO_PIN, 1);
}
