# ctexbook + fontspec 必须用 XeLaTeX 编译。
# 有了这个文件，直接 `latexmk main.tex` 就会走 xelatex，
# 而不会退回 pdflatex 报 “fontspec requires XeTeX”。
$pdf_mode = 5;    # 5 = xelatex -> xdv -> pdf
$synctex = 1;
