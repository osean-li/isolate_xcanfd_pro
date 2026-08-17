# 烧录工具

主机端（电脑上跑）的固件烧录工具。

- **`HPMicro_Manufacturing_Tool_v0.6.0.zip`**：先楫半导体官方编程工具（Windows GUI）。
  - 解压后运行，用于通过**串口**给 HPM5321 烧录固件（QFN48 版本不支持 USB 直烧）。
  - 用法见 [`../firmware/README.md`](../firmware/README.md) 与 [docs/get-started.md](../docs/get-started.md#4-烧录固件)。
- 想用最新版：<https://github.com/hpmicro/hpm_manufacturing_tool/releases>

> 注：此工具为预编译 Windows 程序，体积较大（约 33MB）。如不想纳入 Git 版本库，可加入 `.gitignore` 改从上述链接下载；本仓库默认附带以便新手一站式使用。
