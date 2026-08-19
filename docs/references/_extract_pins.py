import pymupdf, re, sys

ds = pymupdf.open("docs/references/HPM5300DSV012.pdf")
targets = ["UART0_TXD", "UART0_RXD", "CAN0_TXD", "CAN0_RXD",
           "CAN1_TXD", "CAN1_RXD", "GPIO0", "PA24", "PA25"]

seen = set()
for i in range(len(ds)):
    txt = ds[i].get_text()
    if any(t in txt for t in targets):
        # 只打印包含目标行的段落
        for line in txt.splitlines():
            if any(t in line for t in targets):
                key = line.strip()
                if key and key not in seen:
                    seen.add(key)
                    print(f"[p{i+1}] {key}")
