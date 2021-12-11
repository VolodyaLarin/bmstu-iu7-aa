LATEX_ARGS=-shell-escape

bash ./make_plantuml.sh
echo ${LATEX_ARGS}
rm *.aux *.toc *.out *.log *.bbl *.blg
pdflatex ${LATEX_ARGS} rpz.tex
bibtex8 -B rpz
pdflatex ${LATEX_ARGS} rpz.tex 
pdflatex ${LATEX_ARGS} rpz.tex 
