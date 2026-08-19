/*
 * Copyright (c) 2026
 * Custom board header for HPM5321 isolated USB-CAN FD adapter.
 *
 * 5321 属 HPM5300 系列，board 配置以 hpm5300evk 为蓝本裁剪。
 * 本文件仅包含本板自定义的板级宏/引脚定义；通用 board.h 由 SDK 提供。
 */

#ifndef _BOARD_H
#define _BOARD_H

#include "hpm_soc.h"

/* LED：⚠️ 待对照原理图确认（D1/D2 接到哪个 GPIO 引脚）。
 * 若板载无 LED 或不确定，可注释 board_init_led_pins / board_led_* 调用。 */
#define BOARD_LED_GPIO_BASE      GPIO0
#define BOARD_LED_GPIO_PIN       8       /* TODO: 对照原理图修改 */

/* UART0：烧录/调试串口（H1 排针 5/6/7 脚） */
#define BOARD_CONSOLE_UART_BASE  UART0
#define BOARD_CONSOLE_UART_CLK   clock_uart0
#define BOARD_CONSOLE_UART_BAUDRATE 115200

#endif /* _BOARD_H */
