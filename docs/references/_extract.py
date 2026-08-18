import pymupdf, re
ds = pymupdf.open("docs/references/HPM5300DSV012.pdf")
print("==== DS page 17 FULL ====")
print(ds[16].get_text())
