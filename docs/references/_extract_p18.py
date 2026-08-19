import pymupdf, sys
sys.stdout.reconfigure(encoding="utf-8")
ds = pymupdf.open("docs/references/HPM5300DSV012.pdf")
for p in [17, 18, 19]:  # 第18/19/20页
    print(f"\n========== PAGE {p+1} ==========")
    print(ds[p].get_text())
