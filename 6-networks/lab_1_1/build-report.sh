# A bash script to generate a pdf report for lab1 part1.
# Tested on macOS.

# Creating a template for report.
REPORT_TEMPLATES="report_templates"
REPORT_TEX_FILE="report.tex"
REPORT_PDF="report.pdf"
cat "$REPORT_TEMPLATES/report_header.tex" > $REPORT_TEX_FILE
echo "\input{$REPORT_TEMPLATES/title.tex}" >> $REPORT_TEX_FILE

# 1. hostname
echo "\section{hostname util}
\begin{verbatim}" >> $REPORT_TEX_FILE
hostname >> $REPORT_TEX_FILE
echo "\end{verbatim}" >> $REPORT_TEX_FILE

# 2. ipconfig
echo "\section{ipconfig}
\begin{verbatim}" >> $REPORT_TEX_FILE
ifconfig | grep inet >> $REPORT_TEX_FILE
echo "\end{verbatim}" >> $REPORT_TEX_FILE

# Completing tex sources.
echo "\end{document}" >> $REPORT_TEX_FILE

# Compiling report from tex sources.
pdflatex $REPORT_TEX_FILE
rm $REPORT_TEX_FILE
open $REPORT_PDF
