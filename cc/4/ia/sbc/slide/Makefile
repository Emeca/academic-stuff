#======================================
# uhetslide, template para slides
#
# Eder Ruiz Maria
# Paulo Leonardo Benatto
#======================================

LIXO=main.pdf *.aux *.log *.nav *.out *.snm *.toc

all: pdf
	cp main.pdf slide.pdf

pdf: main.tex imagem
	texi2pdf main.tex	

imagem:
	@cd img/ && ebb *.png && cd ..

clean:
	@rm -f ${LIXO}
	@cd img/ && rm -f ${LIXO} && cd ..

help:
	@echo ''
	@echo '============== [help] ==============='
	@echo '|'
	@echo '|Para compilação do slide'
	@echo '|  all           - Executa todas as opções marcadas com [*]'
	@echo '|* imagem        - Gera os arquivos de informação das imagens'
	@echo '|* pdf           - Compila os .tex e gera um pdf'
	@echo '|  clean         - Apaga os arquivos temporários gerados no processo de compilação'
	@echo '|  help          - Exibe esse help'
	@echo '|'
	@echo '============== [help] ==============='
	@echo ''
