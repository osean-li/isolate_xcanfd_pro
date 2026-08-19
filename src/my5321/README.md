# my5321_demo —— HPM5321 最小固件 Demo

> 基于本仓库 `src/sdk_env/` 的 HPM SDK，针对 **HPM5321 隔离 USB‑CAN FD** 板。
> 5321 属 HPM5300 系列，board 配置以 `hpm5300evk` 蓝本裁剪。
> 本 demo 功能：串口打印 + LED 闪烁 + CAN0 回环初始化（便于无分析仪自测）。

## 目录结构
```
my5321/
├─ user_board/            # 板级配置（仿 hpm5300evk）
│  ├─ board.h/.c          # LED / UART / 板级初始化
│  ├─ pinmux.c/.h         # 引脚复用（UART0 / CAN0）
│  └─ user_board.yaml     # soc=HPM5300, openocd-soc=hpm5300
└─ user_app/              # 应用
   ├─ src/main.c          # 最小 demo：打印 + LED + CAN0 loopback
   ├─ inc/board.h         # 转发头
   ├─ linkers/gcc/user_linker.ld  # 复制自 SDK HPM5301 flash_xip.ld
   └─ CMakeLists.txt
```

## 前置条件（见 docs/固件开发环境搭建.md）
- 已用 `start_cmd.cmd` 打开 SDK 环境（设好 HPM_SDK_BASE / 工具链 / cmake）。
- 已装 USB‑TTL 串口驱动（烧录用）。
- 已装 `src/sdk_env/tools/FTDI_InstallDriver.exe`（调试用，可选）。

## 编译（在 start_cmd.cmd 窗口）

### 方式 A：start_gui（零配置，推荐先跑通）
1. 双击 `src/sdk_env/start_gui.exe`。
2. Board Path 选 `src/my5321/`，App Path 选 `src/my5321/`。
3. Build Type = `flash_xip`。
4. 点 Generate → Compile。
5. 产物：`build/my5321_demo_hpm5300_flash_xip.bin`（或类似路径）。

### 方式 B：命令行 ninja
```bat
cd src\my5321\user_app
cmake -G Ninja -B build -DBOARD=my5321 -DCMAKE_BUILD_TYPE=flash_xip
cmake --build build
```
产物：`src/my5321/user_app/build/<app>_hpm5300_flash_xip.bin`

> 注意：Windows 长路径限制——若 ninja 报 "file name too long"，把工程移到盘符根目录（如 `D:\xcanfd\`）再编译。

## 烧录（串口 ISP，无 USB‑Boot）
1. USB‑TTL ↔ H1 排针（模块拨 3.3V）：TX→H1.5、RX→H1.6、GND→H1.7。
2. **按住 SW1** → 接 USB‑C 上电 → 进 ISP 后松开。
3. 打开 `tools/HPMicro_Manufacturing_Tool_v0.6.0/hpm_manufacturing_gui.exe`：
   - 选芯片类别 **HPM5300**，连接 → 载入上面生成的 `.bin` → 烧写。
4. 烧完断开 USB‑C 重插复位，串口（115200）应打印 `hello from my5321`。
5. CLI 等价：`hpm_manufacturing_cmd.exe -p -r "load-image build\<app>_hpm5300_flash_xip.bin"`

## 调试（OpenOCD + GDB，可选）
1. 装好 FT2232 驱动，接 H1 的 SWD/JTAG（1‑4 脚）+ 板载 USB‑C 供电。
2. `start_gui.exe` → 「启动 GDB Server」（OpenOCD，用 hpm5300.cfg + ft2232.cfg）。
3. 用 Segger SES 或 `riscv32-...-gdb` 连 `localhost:3333` 下断点。

## 下一步
- 把 `pinmux.c` 里的 UART/CAN 引脚对照原理图核对（当前为示例值）。
- CAN0 从 loopback 改为正常模式，接 CAN 分析仪发帧验证。
- 参考 `reference/pcan_pro_x/`（STM32）学习 PCAN USB 协议与双通道/隔离功能构成，再用 HPM SDK 驱动重实现。
- 逐步叠加：UART 命令 → CAN 收发 → USB 桥接（SDK 的 cherryusb 示例）。
