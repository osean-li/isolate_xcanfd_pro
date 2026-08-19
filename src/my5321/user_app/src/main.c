/*
 * Copyright (c) 2026
 * Minimal demo for HPM5321 isolated USB-CAN FD adapter.
 *
 * 功能：
 *  1) 串口打印 "hello from my5321"
 *  2) LED 周期闪烁（board_led_toggle 由定时器回调）
 *  3) CAN0 初始化为回环模式（loopback），可接 CAN 分析仪验证
 *
 * 注意（已根据 SDK 源码核对）：
 *  - SDK 的 HPM5301 iomux 头里，QFN48 的 PA 引脚**没有** CAN 复用宏，
 *    CAN 物理引脚需对照本板原理图确认（见 pinmux.c 的 TODO）。
 *  - hpm_can_drv.h 的 can_init 是三参数：can_init(base, &config, src_clk_freq)。
 *  - can_config_t 回环用 mode = CAN_MODE_LOOPBACK（无 enable_loopback 字段）。
 */

#include <stdio.h>
#include "board.h"
#include "hpm_debug_console.h"
#include "hpm_gpio_drv.h"
#include "hpm_can_drv.h"
#include "hpm_clock_drv.h"
#include "hpm_sysctl_drv.h"

#define LED_FLASH_PERIOD_MS 500

/* ---------------- CAN0 最小初始化（loopback，便于无分析仪自测） ---------------- */
static void can0_init_loopback(void)
{
    can_config_t can;
    can_get_default_config(&can);
    can.baudrate = 500000;          /* 仲裁段 500k */
    can.baudrate_fd = 8000000;      /* 数据段 8M（CAN-FD） */
    can.enable_canfd = true;
    can.mode = CAN_MODE_LOOPBACK;   /* 回环：自发自收，无需外部节点 */
    /* 也可用 can.enable_self_ack = true 实现自发自收 */

    /* src_clk_freq：CAN 外设源时钟频率（按本板时钟树填写，常见 80MHz） */
    uint32_t src_clk = clock_get_frequency(clock_node_can0);
    hpm_stat_t st = can_init(CAN0, &can, src_clk);
    if (st == status_success) {
        printf("[can] CAN0 init ok (loopback, 500k/8M CAN-FD)\n");
    } else {
        printf("[can] CAN0 init failed: %d\n", st);
    }
}

int main(void)
{
    board_init();
    board_init_led_pins();

    /* 创建定时器，周期翻转 LED */
    board_timer_create(LED_FLASH_PERIOD_MS, board_led_toggle);

    printf("hello from my5321 (HPM5321 / HPM5300 series)\n");

    can0_init_loopback();

    while (1) {
        board_delay_ms(1000);
        printf("tick\n");
    }
    return 0;
}
