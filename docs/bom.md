# BOM（物料清单）

> 数据来源：本仓库 [`hardware/BOM_Board1_Schematic1_2026-08-12.xlsx`](../hardware/BOM_Board1_Schematic1_2026-08-12.xlsx)（立创 EDA 导出，实测）。
> 共 **26 种物料**，元件总数约 **60 颗**。所有阻容均为 0603 / 0805 / 0402 等常用贴片封装，方便手焊。

## 总览（按功能区块）

| 功能区块 | 主要物料 |
| --- | --- |
| 主控核心 (CORE) | U1 HPM5321、X1 24MHz、L1 4.7uH、退耦 / 滤波电容、电阻、SW1、H1、D1 / D2 |
| USB 接口 (USB) | USB1 Type‑C、R10 / R11（CC）、D6（ESD） |
| 电源 + CAN + 隔离 (CAN/POWER) | LDO1、U2 隔离 DC‑DC、U5 隔离器、U3 / U4 收发器、CN1 / CN2、R8 / R9、SW2、D3 / D4 / D5、滤波电容 |

## 完整清单

| # | 位号 | 数量 | 封装 | 参数 / 值 | 厂商型号 | 厂商 | 立创料号 | 作用 |
|---|------|------|------|-----------|----------|------|----------|------|
| 1 | C1, C2 | 2 | C0603 | 22pF | CL10C220JB8NNNC | SAMSUNG | C1653 | 晶振负载电容 |
| 2 | C3, C4, C5, C7, C8, C9, C10, C11, C12, C13, C14, C15, C17, C19, C24, C29 | 16 | C0603 | 100nF | CC0603KRX7R9BB104 | YAGEO | C14663 | 退耦电容（每电源脚旁一颗） |
| 3 | C6, C25, C26 | 3 | C0603 | 10uF | CL10A106KP8NNNC | SAMSUNG | C19702 | 电源滤波 |
| 4 | C16, C18 | 2 | C0603 | 4.7uF | CL10A475KO8NNNC | SAMSUNG | C19666 | 电源滤波 |
| 5 | C20, C21 | 2 | C0603 | 22uF | CL10A226MQ8NRNC | SAMSUNG | C59461 | 内核电源滤波 |
| 6 | C22, C23, C27, C28 | 4 | C0603 | 1uF | CL10A105KB8NNNC | SAMSUNG | C15849 | 电源滤波 |
| 7 | CN1, CN2 | 2 | CONN‑TH_3P‑P3.81 | KF2EDGR‑3.81‑3P | KF2EDGR‑3.81‑3P | KEFA | C441183 | CAN 接线端子（CANH / CANL / GND） |
| 8 | D1, D2 | 2 | LED‑TH | A694B/2SYG/S530‑E2 | A694B/2SYG/S530‑E2 | EVERLIGHT | C93880 | 状态 LED（黄绿） |
| 9 | D3 | 1 | SOD‑123 | SMF5.0CA | SMF5.0CA | AnBon | C435453 | TVS 浪涌 / 过压保护（5V） |
| 10 | D4, D5 | 2 | SOT‑23‑3 | PESD1CAN | PESD1CAN | UMW | C2687121 | CAN 引脚 ESD 保护 |
| 11 | D6 | 1 | SOT‑23‑6 | USBLC6‑2SC6 | USBLC6‑2SC6 | TECH PUBLIC | C2827654 | USB 接口 ESD 保护 |
| 12 | H1 | 1 | HDR‑TH_8P‑P2.54 | X6511WV‑08H‑C60D30 | X6511WV‑08H‑C60D30 | XKB | C706880 | 调试 / 烧录排针 1×8 |
| 13 | L1 | 1 | IND‑SMD_L2.5‑W2.0 | SWPA252012S4R7MT（4.7uH） | SWPA252012S4R7MT | Sunlord | C87640 | 功率电感（内部 DCDC） |
| 14 | LDO1 | 1 | SOT‑23‑5 | ME6211C33M5G‑N（5V→3.3V） | ME6211C33M5G‑N | MICRONE | C82942 | 系统 3.3V 稳压 |
| 15 | R1, R2, R3, R4 | 4 | R0603 | 5.1kΩ | 0603WAF5101T5E | UNI‑ROYAL | C23186 | MCU 配置 / 上下拉 |
| 16 | R5, R6, R7 | 3 | R0603 | 10kΩ | 0603WAF1002T5E | UNI‑ROYAL | C25804 | 上拉电阻 |
| 17 | R8, R9 | 2 | R0805 | 120Ω | 0805W8F1200T5E | UNI‑ROYAL | C17437 | CAN 终端电阻 |
| 18 | R10, R11 | 2 | R0402 | 5.1kΩ | 0402WGF5101TCE | UNI‑ROYAL | C25905 | USB CC1 / CC2 下拉（Rd） |
| 19 | SW1 | 1 | SW‑SMD_4P | TS‑KG89S‑AT25F | TS‑KG89S‑AT25F | HANBO | C2874599 | 4 位拨码（BOOT / 配置） |
| 20 | SW2 | 1 | SW‑TH_DP‑02XP | DP‑02RP | DP‑02RP | 韩荣 | C129041 | 2 位琴键（终端电阻切换） |
| 21 | U1 | 1 | QFN‑48 | HPM5321IEG1 | HPM5321IEG1 | HPMICRO | C49451867 | 主控 MCU（RISC‑V，USB 高速 + 2×CAN‑FD） |
| 22 | U2 | 1 | PWRM‑TH | B0505S‑1WR3 | B0505S‑1WR3 | EVISUN | C7465178 | 隔离 DC‑DC（5V→隔离 5V，1500V） |
| 23 | U3, U4 | 2 | SOP‑8 | SIT1051AT/3 | SIT1051AT/3 | SIT（芯力特） | C5382551 | CAN‑FD 收发器 ×2 通道 |
| 24 | U5 | 1 | SOIC‑16 | CA‑IS3742HW | CA‑IS3742HW | Chipanalog（川土微） | C528654 | 4 通道数字隔离器 |
| 25 | USB1 | 1 | USB‑C‑SMD | TYPEC‑304‑BCP16 | TYPEC‑304‑BCP16 | XUNPU | C720629 | Type‑C 母座（取电 + 通信） |
| 26 | X1 | 1 | CRYSTAL‑SMD_4P | XL2EL89COI‑111YLC‑24M（24MHz） | XL2EL89COI‑111YLC‑24M | YXC | C5444545 | 系统主时钟晶振 |

## 备注 / 勘误

- **CAN 收发器型号**：本 BOM 实测为 **SIT1051AT/3**（芯力特）。主教程 HTML 中曾写作 SIT1042，二者引脚兼容、均为芯力特 CAN‑FD 收发器，以本 BOM 为准。
- **电阻封装**：原 OSHWHub 公开 BOM 标注 R1–R7 为 0402，本 `_copy` 工程实际为 R0603（R1–R7）/ R0805（R8, R9）/ R0402（R10, R11），以本工程实测为准。
- 所有立创料号（LCSC）均为「示例可替代」，实际下单以当时库存与价格为准；同参数、同封装的国产料基本可互换。
- 完整电源 / 网络信息见 [`docs/tutorial.html`](tutorial.html) 第 4、10 章，或原 EDA 工程。

## 待实物核对（2026-08-16 复查发现）

- ✅ **D3 封装已确认**：第 9 行 SMF5.0CA / SOD‑123 / AnBon（安邦）/ 立创 C435453 正确；原照片文件名 `SMBJ5.0CA.jpg` 系命名笔误，已重命名为 `SMF5.0CA.jpg`，与 BOM 一致（2026-08-16 用户拍摄包装标签核对）。
- ✅ **U1 型号已确认**：第 21 行 HPM5321IEG1 正确；原照片文件名 `HPM5321IEC1.jpg` 系命名笔误，已重命名为 `HPM5321IEG1.jpg` 与 BOM 一致（2026-08-16 用户确认）。
- ℹ️ **照片文件名转录差异（非 BOM 错误）**：`SW1`（TS‑KG89S‑AT25F vs 照片 FS‑KC8S‑AT25F）、`H1`（X6511WV‑08H‑C60D30 vs 照片 X6511WW‑08H‑C60D30）、`X1`（XL2EL89COI‑111YLC‑24M vs 照片 XL2EL89C01‑11YLC‑24M）文件名与 BOM 型号有字符差异，疑似 OCR / 命名笔误（如 O↔0、I↔1、V↔W），功能件一致，焊前对照实物即可。
