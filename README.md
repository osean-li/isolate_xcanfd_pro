# HPM5321 高速隔离 USB‑CAN FD 工具 · 从零学硬件开源教程

> 一块真实开源板卡的硬件入门教材：用「USB 转 CAN FD 隔离适配器」带你从零看懂原理图、PCB 与焊接调试。

[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](LICENSE)
![语言](https://img.shields.io/badge/语言-中文-red.svg)
![难度](https://img.shields.io/badge/难度-新手友好-brightgreen.svg)
[![主教程](https://img.shields.io/badge/文档-tutorial.html-orange.svg)](docs/tutorial.html)

## 📌 这是什么

这是一个 **USB 转 CAN FD** 的适配器开源项目，同时是一份**写给小白的硬件入门教程**。

- 电脑只有 USB 口，汽车 / 工业设备用 CAN（CAN FD）总线。这块板子夹在中间做「翻译官」。
- 主控是国产 **HPM5321（RISC‑V）**，自带 USB 高速和 2 路 CAN‑FD。
- 对 CAN 侧做了 **1500V 电气隔离**——这是它最核心的设计亮点。
- 兼容 **PCAN‑FD PRO**，电脑装好驱动即可用 PCAN‑View / TSMaster 等上位机。

本项目把原开源硬件（见文末链接）整理成**适合新手学习的文档 + 资料结构**，让你边看真实板卡边学硬件。

## 🎯 给谁看 / 项目目标

- 想入门**硬件 / PCB / 嵌入式**但不知道从哪下手的同学
- 学过一点电子，但看不懂**原理图**和**数据手册**的人
- 想自己**打板、焊接、烧录**一块真实板子练手的人

目标只有一句：**把一块真实板卡拆开讲透，让硬件不再吓人。**

## ✨ 项目亮点

- 📖 **零基础友好**：从「电压 / 电流 / 电阻」讲起，每个概念都用本板真实元件举例
- 🧩 **真实工程**：4 层板、FR‑4、CAN 电气隔离 1500V、兼容 PCAN‑FD
- 🛡️ **隔离设计专题**：详细拆解「电源隔离 + 信号隔离」两件套
- 🔧 **手焊实战**：8 阶段焊接调试流程 + 万用表口诀 + 可打印核查清单
- 🗂️ **结构清晰**：原理图 / BOM / 教程 / 固件说明分目录管理

## 📚 你会学到什么

1. 硬件世界的基本语言：电压、电流、电阻、网络、数字信号
2. 电子元器件 ABC：电阻 / 电容 / 电感、二极管 / LED / TVS / ESD、晶振、连接器、芯片
3. 看懂原理图：符号 vs 封装、位号、网络、分页
4. 拆解本板功能模块：USB 供电、电源系统、隔离屏障、CAN 收发、主控配置
5. PCB 入门到进阶：层 / 焊盘 / 过孔、为什么用 4 层、叠层与阻抗、差分对、DRC / DFM
6. 整机信号流向串讲
7. 动手焊接、调试、烧录、装驱动、验收

## 🗺️ 推荐学习路径

按顺序看 [`docs/tutorial.html`](docs/tutorial.html) 的 12 个章节即可：

```
0  这块板子是干嘛的
1  硬件世界的基本语言
2  电子元器件 ABC
3  看懂原理图
4  本板功能模块拆解   ← 重头戏
5  PCB 设计入门
6  PCB 设计进阶实战
7  整机信号流向
8  动手：焊接与调试
9  动手：烧录与驱动
10 完整 BOM 表
11 术语表 & 延伸阅读
```

## 🚀 快速上手（三步走）

1. **读教程**：打开 [docs/tutorial.html](docs/tutorial.html)（网页版，带图解）
2. **拿板子**：二选一
   - 懒人版：在嘉立创一键下单 PCBA（见教程 6.4）
   - 硬核版：按 [docs/bom.md](docs/bom.md) 买料，自己手焊
3. **焊 + 烧 + 测**：按 [docs/get-started.md](docs/get-started.md) 的 8 阶段流程操作

> 没板子也能学：教程里的图全是本板实况，对着看就行。

## 📂 仓库目录结构

```
.
├── README.md                                  # 你正在看的首页
├── LICENSE                                    # GPL-3.0
├── CONTRIBUTING.md                            # 如何参与
├── CODE_OF_CONDUCT.md                         # 社区行为准则
├── docs/
│   ├── tutorial.html                          # 【主教程】从零学硬件（网页版，带 SVG 图解）
│   ├── get-started.md                         # 新手快速上手（焊接收调流程）
│   ├── design-rationale.md                   # 基于原理图的设计理由拆解（为什么这样设计）
│   ├── hardware-knowledge-applied.md         # 学习笔记如何在本项目落地（知识→实践对照）
│   ├── my-build-log.md                       # 我的实物调试日志（项目经历核心证据）
│   ├── bom.md                                 # 完整物料清单（含立创料号）
│   └── glossary.md                            # 术语表
├── hardware/
│   ├── HPM5321高速隔离USBCANFD工具_原理图.pdf  # 原理图（PDF 导出）
│   ├── BOM_Board1_Schematic1_2026-08-12.xlsx  # BOM 源文件（立创导出）
│   └── ProPrj_HPM5321 高速隔离USBCAN FD工具_2026-08-07.epro2  # 立创 EDA 工程（原理图+PCB 源文件，可编辑）
├── firmware/
│   ├── README.md                             # 固件烧录说明
│   └── FDFW_20260201.bin                      # 固件镜像（拿来就能烧）
├── tools/
│   └── HPMicro_Manufacturing_Tool_v0.6.0.zip  # 先楫官方烧录工具（主机端）
├── reference/
│   └── pcan_pro_x/                           # 【参考实现】社区 PCAN-PRO 克隆固件(STM32F4)，仅学 PCAN USB 协议，不能在 HPM5321 运行
└── enclosure/
    ├── 外壳.3mf                               # 外壳 3D 模型（3MF，可直接切片打印）
    └── 外壳.STEP                              # 外壳 3D 模型（STEP，可 CAD 编辑）
```

> ⚠️ `reference/pcan_pro_x/` 是第三方 STM32F4 参考固件（社区 PCAN-PRO 克隆），**不能在 HPM5321 上运行**，仅作 PCAN USB 协议学习用；详情与许可证见其内 `README.md`。

## 📖 文档导航

| 文档 | 说明 |
|------|------|
| [docs/tutorial.html](docs/tutorial.html) | 主教程，零基础全覆盖，强烈推荐从头看 |
| [docs/get-started.md](docs/get-started.md) | 最短路径：怎么拿到板子并让它跑起来 |
| [docs/design-rationale.md](docs/design-rationale.md) | 基于原理图，逐模块说明"为什么这样设计" |
| [docs/hardware-knowledge-applied.md](docs/hardware-knowledge-applied.md) | 我的硬件知识如何在本项目落地（知识→实践对照，作品集证据） |
| [docs/my-build-log.md](docs/my-build-log.md) | 我的实物调试日志（debug 故事 + 配图，简历素材） |
| [docs/bom.md](docs/bom.md) | 买料清单，含厂商型号与立创料号 |
| [docs/glossary.md](docs/glossary.md) | 看不懂的名词来这查 |

## 🔧 硬件资料

- 原理图：[hardware/HPM5321高速隔离USBCANFD工具_原理图.pdf](hardware/HPM5321高速隔离USBCANFD工具_原理图.pdf)
- BOM 源文件：[hardware/BOM_Board1_Schematic1_2026-08-12.xlsx](hardware/BOM_Board1_Schematic1_2026-08-12.xlsx)
- 固件镜像：[firmware/FDFW_20260201.bin](firmware/FDFW_20260201.bin)（拿来就能烧）
- 烧录工具：[tools/HPMicro_Manufacturing_Tool_v0.6.0.zip](tools/HPMicro_Manufacturing_Tool_v0.6.0.zip)（先楫官方，主机端）
- 外壳 3D 模型：[enclosure/](enclosure/)（`外壳.3mf` 可直接切片打印，`外壳.STEP` 可 CAD 编辑）
- EDA 工程（原理图 4 页 + PCB 源文件）：[hardware/ProPrj_HPM5321 高速隔离USBCAN FD工具_2026-08-07.epro2](hardware/ProPrj_HPM5321%20高速隔离USBCAN%20FD工具_2026-08-07.epro2)（嘉立创 EDA 专业版，双击即可打开编辑）；也可见于原开源项目主页

## 🤝 如何参与

欢迎 PR / Issue！无论是**改错别字、补图、翻译、订正 BOM，还是分享你的焊接翻车经验**，都对后来者很有帮助。

详见 [CONTRIBUTING.md](CONTRIBUTING.md)。

## 📜 开源协议

本项目以 **GNU GPL‑3.0** 发布（见 [LICENSE](LICENSE)）。

- ✅ 可以：学习、修改、再分发、用于教学
- ⚠️ 注意：若分发或修改后分发，**必须开源你的改动**；原项目注明 GPL‑3.0，**未经授权禁止商用**。

## 🌐 相关资源

- 原开源硬件项目（OSHWHub）：<https://oshwhub.com/eda_kwazdnpkc/hpm5321_pcan>
- HPMicro 先楫半导体（HPM5321 资料）：<https://www.hpmicro.com>
- 烧录工具 HPMicro_Manufacturing_Tool（GitHub Releases）
- PCAN 驱动（PEAK 官网）/ 上位机 PCAN‑View、TSMaster、Linux SocketCAN

## 🇬🇧 English Abstract

A beginner-friendly open-source hardware + tutorial project built around a **HPM5321 (RISC‑V) high-speed isolated USB‑CAN FD adapter**. The repo turns a real open-hardware board into a step-by-step "learn hardware from zero" course: schematics reading, PCB basics (4-layer, 1500V isolation, differential pairs), hands-on soldering / flashing, plus a full BOM with LCSC part numbers. Licensed under GPL‑3.0.

## 🙏 致谢

- 原硬件开源作者（OSHWHub `eda_kwazdnpkc`）
- HPMicro、川土微、芯力特、南京微盟等国产芯片厂商
- 所有愿意把「翻车经验」写下来分享的硬核玩家

---

⭐ 如果这份教程帮你入了门，点个 Star 让更多人看到。
