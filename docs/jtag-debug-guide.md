# JTAG 断点调试指南（HPM5321 隔离 USB-CAN FD 适配器）

> 本文讲清楚：如何用 JTAG + GDB 在这块板子上做**单步 / 断点 / 看变量**调试。
> 硬件接口（H1 排针）已经引好了，真正的前提是**有一份带调试符号的固件 `.elf`**。

---

## 0. 前置条件（最重要）

JTAG 断点调试 = 硬件接口 + 调试探针 + 带符号的 `.elf`。三者缺一不可。

- ✅ **硬件接口已就绪**：H1 的 pin1~4 就是 JTAG 的 TDO/TDI/TCK/TMS，pin7 是 GND。
- ✅ **调试探针**：见 §1，自己买一个支持 RISC-V 的。
- ⚠️ **带符号固件**：仓库现状——
  - `firmware/FDFW_20260201.bin` 是**裸二进制，无源码、无符号** → 没法按函数名下断点。
  - `reference/pcan_pro_x/` 是 **STM32F4（ARM Cortex-M4）的 PCAN 协议栈参考**，不是 HPM5321 固件，只能借鉴协议逻辑，不能直接编译烧到本板。
  - **结论**：要真正做断点调试，必须先有/自己写一份基于 `hpm_sdk` 的 HPM 固件源码，用 `-g` 编译出 `.elf`。这恰好是你简历要的"**原创固件贡献**"——调试能力是建立在自己写的代码之上的。

> HPM5321 调试子系统：支持 JTAG + **RISC-V External Debug Support v0.13**（IEEE 1149.1），内置 Debug Module（含 Trigger Module，可设硬件断点/数据观察点）。所以硬件断点是原生支持的。

---

## 1. 需要的硬件

调试探针（三选一，都要支持 RISC-V）：

| 探针 | 说明 | 备注 |
|---|---|---|
| **J-Link**（EDU / BASE / 正版） | 最稳、最快，断点不易丢 | 需固件支持 RISC-V（较新型号都支持）；可用 Segger 自家 GDB Server |
| **DAP-Link** + riscv-openocd | 便宜/开源 | 需支持 JTAG 的固件（HPM 上游 PR #2578 加了 DAP JTAG 支持） |
| **FT2232H** + riscv-openocd | 官方 HPM 开发板同款方案 | 自由度高，配置略繁琐 |

外加：杜邦线若干、板子自己的 USB-C 供电线。

---

## 2. 接线（H1 ↔ 探针）

交叉/直连对照（JTAG 是直连，不分收发）：

| H1 脚 | H1 信号 | 接探针脚 | 说明 |
|---|---|---|---|
| 1 | TDO | 探针 TDO | 数据出（芯片→探针） |
| 2 | TDI | 探针 TDI | 数据入（探针→芯片） |
| 3 | TCK | 探针 TCK | 调试时钟 |
| 4 | TMS | 探针 TMS | 模式选择 |
| 7 | GND | 探针 GND | **必须接**，信号回流 |
| — | — | 探针 VCC/VTref | **不接**（板子自供电，避免双电源） |

- **松开 SW1**（BOOT 按键，正常运行模式；按住进 ISP 就跑不了你的固件）。
- 板子单独用 USB-C 上电；探针只是"旁观+控制"，不供电。

---

## 3. 软件工具链

- **编译器**：RISC-V GNU 工具链 `riscv-none-embed-gcc`（建议 10.2.0）。
  编译架构参数（HPM5300 是 32 位 RISC-V）：
  ```
  -march=rv32imafdc -mabi=ilp32d
  ```
- **调试服务器**（二选一）：
  - `hpmicro/riscv-openocd`（HPM 官方 OpenOCD 分支，自带 `hpm5321.cfg` 目标配置，免费、支持多种探针）；
  - 或 Segger **J-Link GDB Server**（J-Link 用户，稳定性更好）。
- **SDK**：`hpm_sdk`（提供 `hpm5321.cfg` / 链接脚本 / CAN-FD·USB·UART 外设驱动）。
- **GDB 客户端**：工具链里的 `riscv-none-embed-gdb`。
- **可选 IDE**：VS Code + Cortex-Debug 插件；或 Segger **Ozone**（J-Link 免费，图形化调试体验最好）。

---

## 4. 编译带调试符号的固件

关键：加 `-g`（调试信息）和 `-Og`/`-O0`（别让优化把代码改得对不上源码行）。

CMake 示例（`CMakeLists.txt` 片段）：
```cmake
add_executable(firmware.elf src/main.c ...)
target_compile_options(firmware.elf PRIVATE
    -march=rv32imafdc -mabi=ilp32d
    -g -Og                  # ← 调试符号 + 低优化
    -Wall
)
# 链接脚本由 hpm_sdk 提供，.text 落在 Flash 基址 0x80000000
```
产出 `build/firmware.elf`（**不是 .bin**）——`.elf` 里含符号表，GDB 才能按函数名 `break main`。

> 想烧录这个 `.elf` 到 Flash，可在 GDB 里 `load`（见 §6），或用 `HPMicro_Manufacturing_Tool` 烧对应的 `.bin`。

---

## 5. 启动调试服务器

**方案 A：OpenOCD（免费，支持 J-Link / DAP-Link / FT2232）**
```bash
# J-Link
openocd -f interface/jlink.cfg -f target/hpm5321.cfg
# DAP-Link
openocd -f interface/cmsis-dap.cfg -f target/hpm5321.cfg
```
> `hpm5321.cfg` 随 `hpm_sdk` / `riscv-openocd` 自带；若没有就用 `hpm5300.cfg`（同内核）。
> 成功会监听 **3333**（GDB）和 4444（Telnet）端口。

**方案 B：J-Link GDB Server（J-Link 用户更稳）**
```bash
JLinkGDBServer -device HPM5321 -if JTAG -speed 10000 -port 3333
```

---

## 6. GDB 调试会话

另开一个终端：
```bash
riscv-none-embed-gdb build/firmware.elf

(gdb) target remote localhost:3333     # 连上 OpenOCD / J-Link GDB Server
(gdb) monitor reset halt               # 复位并立即停住，进入已知状态
(gdb) load                             # 把 .elf 烧进 Flash（覆盖旧固件）
(gdb) break main                       # 在 main() 入口下断点
(gdb) continue                         # 跑，会在 main 停下（或 c）
(gdb) step                             # 单步（进函数，或 s）
(gdb) next                             # 单步（不进函数，或 n）
(gdb) print counter                    # 看变量
(gdb) info registers                   # 看所有寄存器
(gdb) backtrace                        # 调用栈
(gdb) continue                         # 继续跑
```
常用技巧：
- `monitor reset halt` 永远在 `load` 之前做，保证芯片状态干净。
- 命不中、程序跑飞 → 查链接脚本 `.text` 是否落在 Flash 基址 `0x80000000`，向量表首字是否为栈顶、次字为 `Reset_Handler`。
- 把常用命令写进 `.gdbinit`，`riscv-none-embed-gdb -x .gdbinit` 一键启动。

---

## 7. 断点的两种实现（RISC-V 调试机制）

RISC-V 通过 **Debug Module 里的 Trigger Module** 实现断点，两种方式：

| 类型 | GDB 命令 | 原理 | 适用 |
|---|---|---|---|
| **软件断点** | `break` / `b` | 把目标地址的指令临时换成 `ebreak`（或 `c.ebreak`），命中后恢复 | RAM 代码；Flash 靠 OpenOCD 打补丁（部分目标受限） |
| **硬件断点** | `hbreak` / `hb` | 用调试模块的地址匹配触发器，**不改代码** | Flash / ROM / 中断向量等任何地址；数量有限（几个） |
| **数据观察点** | `watch` / `rwatch` / `awatch` | 用触发器监控某内存地址的读/写 | 查"谁改了我的变量" |

- 调试模块进入 Debug Mode 的优先级：**trigger module（硬件断点）> EBREAK（软件断点）> halt-on-reset > 外部 halt 请求 > 单步**。
- 经验：在 Flash 里的代码用 `break` 偶尔失效，就改用 `hbreak`；硬件断点数量有限，关键位置才用。

---

## 8. 不想敲命令？用 IDE

- **VS Code + Cortex-Debug**：配置 `launch.json` 指向 OpenOCD，图形化下断点、看变量、调用栈。
- **Segger Ozone**（J-Link 免费）：图形化调试体验最好，断点稳定、单步流畅，强烈推荐 J-Link 用户。

---

## 9. 常见坑

1. **没源码 / 没加 `-g`** → 只能按地址下断点，看不到函数名和变量。先有 `.elf`。
2. **按住 SW1（BOOT 按键）上电** → 芯片进 ISP 模式，不跑你的固件，断点永远不命中。
3. **探针 VCC 接到 H1** → 双电源打架；探针 VCC/VTref **悬空**。
4. **GND 没接** → 信号无回流，OpenOCD 认不到设备。
5. **Flash 里 `break` 失效** → 改用 `hbreak`（硬件断点）。
6. **链接脚本 `.text` 不在 `0x80000000`** → 上电跑飞，断点白设。

---

## 10. 与本项目的关系（原创贡献路径）

- 想真正用上 JTAG 断点调试 = 你需要**自己基于 `hpm_sdk` 写/移植一份 HPM5321 固件**，用 `-g` 编译。这正是项目目标里"**原创固件贡献**"的落地方式：调试日志 + 源码归属，比只聚合第三方 `.bin` 更有说服力。
- `reference/pcan_pro_x/`（STM32F4 + CMSIS）是 PCAN 协议栈的**参考实现**，可借鉴其 PCAN 帧格式 / 命令处理逻辑，但需移植到 HPM5321 的外设驱动（CAN-FD 控制器、USB HS 设备、UART0）上。
- 第一次成功 `break main` 并单步跑通的截图 + 记录，直接写进 `docs/my-build-log.md`——这是你"嵌入式/硬件工程师"简历的硬核证据。
