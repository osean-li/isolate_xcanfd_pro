/*
 * Copyright (c) 2026
 * Pinmux for HPM5321 isolated USB-CAN FD adapter.
 *
 * ⚠️ 重要：引脚分配需对照本板原理图最终确认。
 * 已确认（来自 SDK hpm_iomux.h，HPM5301/5321）：
 *   - UART0_TXD = PA00 (ALT2)
 *   - UART0_RXD = PA01 (ALT2)      ← 对应 H1 排针 DBG_TX/DBG_RX（3.3V）
 * 未确认（SDK 的 QFN48 iomux 头里 PA 组无 CAN 复用宏，需看原理图）：
 *   - CAN0 / CAN1 的 TX/RX 接到 MCU 的哪个物理脚（可能是 PB/PE 组，
 *     且需确认 SDK 是否提供对应 IOC_PAxx_FUNC_CTL_CANx_xxx 宏）。
 *   - LED 接到哪个 GPIO。
 */

#include "board.h"
#include "hpm_pad_drv.h"
#include "hpm_uart_drv.h"
#include "hpm_can_drv.h"

void board_init_pinmux(void)
{
    /* ---------- UART0 (console / 烧录调试) ---------- */
    HPM_IOC->PAD[IOC_PAD_PA00].FUNC_CTL = IOC_PA00_FUNC_CTL_UART0_TXD;
    HPM_IOC->PAD[IOC_PAD_PA01].FUNC_CTL = IOC_PA01_FUNC_CTL_UART0_RXD;

    /* ---------- CAN0 / CAN1 ----------
     * TODO: 待对照原理图填入真实引脚与 SDK 宏。
     * 例如（示例，需验证 SDK 是否提供该宏）：
     *   HPM_IOC->PAD[IOC_PAD_PBxx].FUNC_CTL = IOC_PBxx_FUNC_CTL_CAN0_TXD;
     *   HPM_IOC->PAD[IOC_PAD_PBxx].FUNC_CTL = IOC_PBxx_FUNC_CTL_CAN0_RXD;
     * 若 SDK 头里无 CAN 宏，可改用原始 ALT 值：
     *   HPM_IOC->PAD[IOC_PAD_PBxx].FUNC_CTL =
     *       (uint32_t)IOC_PAD_FUNC_CTL_ALT_SELECT_SET(7);  // 7 = CANx
     */
}
