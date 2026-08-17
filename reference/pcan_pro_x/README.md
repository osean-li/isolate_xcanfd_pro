# 参考实现代码：PCAN-PRO 克隆固件（STM32F4）

> ⚠️ 本目录是**第三方参考实现**，仅用于学习，不是本项目的固件。

## 它是什么
- 社区开源的 **PCAN-PRO 克隆固件**（上游：[moonglow/pcan_pro_x](https://github.com/moonglow/pcan_pro_x)）。
- 目标硬件：**STM32F4（ARM Cortex-M4）** 开发板，用 `arm-none-eabi-gcc` + STM32 HAL + ST USB 设备库构建。
- 作用：让一块通用 STM32F4 板子在 PEAK 驱动（PCAN-View / PCAN-Basic）下被识别为 PCAN-USB Pro / Pro FD / FD 设备。
- 源码要点：`Src/pcanpro_*.c`（主循环 / CAN / LED / USB 设备 / 协议），以及 `pcan_usbpro_fw.h` / `pcanfd_usb_fw.h` / `pcanfd_ucan.h`（定义 PCAN 的 USB 命令与帧结构）。

## ⚠️ 关键：它不能在 HPM5321 上运行
本项目主控是 **HPM5321（RISC-V RV32）**，这份固件是 **STM32F407（ARM Cortex-M4）**——
**无法为 HPM5321 编译或烧录**。它对我们的唯一价值是**参考**：用来理解 PCAN USB 协议，以及"USB-CAN FD 适配器"是怎么搭出来的。
本项目真正的固件在 `../firmware/`（`FDFW_20260201.bin`，由 HPMicro SDK 提供，PCAN 兼容性在 HPMicro 侧实现）。

## 许可证
- 仓库整体：**WTFPL**（见本目录 `LICENSE`）。
- 三个 PEAK 协议头（`pcan_usbpro_fw.h` / `pcanfd_usb_fw.h` / `pcanfd_ucan.h`）：**GPL-2.0-or-later**（来自 Linux 内核 `peak_usb` 驱动，Copyright PEAK System-Technik GmbH）。
- 两者均与本仓库的 **GPL-3.0** 兼容。

## 版权声明（ACHTUNG，务必保留）
上游作者曾应 **PEAK-System** 要求，移除了 USB 描述符中受版权保护的 **VID/PID 与厂商/产品字符串**（见上游 Issue #16）。
本拷贝的 `Src/usbd_desc.c` 已改用 **ST 的 VID `0x0483`** 与 **"XCAN"** 品牌，**不含任何 PEAK 标识**。
- ✅ 可以学习、修改、再分发（遵守 WTFPL / GPL-2.0）。
- ❌ **请勿把 PEAK 的 VID/PID 或 "PCAN" / "PEAK" 字符串加回本目录。**

## 本目录已做瘦身（相对上游完整树）
为控制仓库体积，已删除本固件**未使用**的部分，保留阅读与在 STM32F407 上重建所需的全部内容：
- 删除未使用的 CMSIS 子目录：`Lib`（预编译数学库）、`DSP`、`NN`、`RTOS`、`RTOS2`、`Core_A`、`docs`；
- 设备头仅保留 **STM32F407** 所需（`stm32f4xx.h` / `stm32f407xx.h` / `system_stm32f4xx.h`）；
- HAL `Src` 仅保留 `Makefile` 实际编译的 **19 个 `.c`**（CAN / USB-PCD / RCC / Flash / GPIO / DMA / PWR / TIM 等）。
完整未裁剪的源码树请见上游仓库。

## 如何自建（可选，需 arm-none-eabi-gcc）
```bash
make pro       # XCAN PRO 固件（仅 USB HS）
make pro_fd    # XCAN PRO FD 固件
make fd        # XCAN FD 固件（USB FS/HS）
```
> 注意：即使构建成功，也只适用于 STM32F4 板，与本项目的 HPM5321 无关。

## 目录结构
```
pcan_pro_x/
├── Src/                 # 固件源码（PCAN 协议 / CAN / USB 设备 / LED / 时间戳）
├── Drivers/
│   ├── CMSIS/           # 已精简：仅保留 F407 需要的核头与设备头
│   └── STM32F4xx_HAL_Driver/   # 已精简：仅保留 Makefile 用到的 HAL 源
├── Middlewares/ST/STM32_USB_Device_Library/  # ST USB 设备库（小）
├── STM32F407VGTx_FLASH.ld   # 链接脚本
├── startup_stm32f407xx.s     # 启动文件
├── Makefile
├── LICENSE              # WTFPL
└── README.md            # 本说明
```
