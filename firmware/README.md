# 固件说明

本仓库已附带可直接烧录的固件与工具，**新手无需再到处找**：

- `FDFW_20260201.bin` — 固件镜像（拿来就能烧，版本 3.x，支持 8Mbps BRS）
- 烧录工具在仓库根目录的 [`../tools/`](../tools/) 下：`HPMicro_Manufacturing_Tool_v0.6.0.zip`（先楫官方，Windows GUI）

> 想用更新版本？可从 HPMicro 官方 GitHub Releases 获取：<https://github.com/hpmicro/hpm_manufacturing_tool/releases>

## 烧录方法

见 [docs/get-started.md](../docs/get-started.md#4-烧录固件) 与教程第 9 章。

要点：

- HPM5321 的 **QFN48 版本不支持 USB 直烧**，必须用**串口** + HPMicro_Manufacturing_Tool
- USB 转串口接排针 **H1**（`TX↔RX` 交叉、`GND` 共地、模块拨 **3.3V**）
- 按住 **SW1（BOOT 按键）** 再上电，进 ISP 模式后松开
- 工具里载入本目录的 `FDFW_20260201.bin` → 连接 → 烧写 → 复位

> 如果你有适配本板的开源固件，欢迎在遵守 GPL‑3.0 的前提下补充到本目录并提 PR。
