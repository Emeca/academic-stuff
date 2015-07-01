LIXO = main.pdf *.aux *.log *.nav *.out *.snm *.toc

all: help

pdf: main.tex 
	texi2pdf main.tex	
	cp main.pdf slide.pdf

clean:
	@rm -f ${LIXO}
	@cd img/ && rm -f ${LIXO} && cd ..

help:
	@echo 'targets:'
	@echo ' * pdf   -> compila os .tex e gera um pdf'
	@echo ' * clean -> apaga os arquivos temporários gerados no processo de compilação'
