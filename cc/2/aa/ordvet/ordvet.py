#!/usr/bin/python
# -*- coding: <'utf-8'> -*-

from sys import argv
from time import *
import pdb

def load_file(nome_do_arquivo):

	V = []
	F = file(nome_do_arquivo,'r')
	linhas = F.readlines()
	F.close
	for i in linhas:
		V.append(int(i.strip()))
	return V	


def print_vetor(V):

	for i in range(int(len(V))):
		print V[i]

def print_help():

	print
	print 'Sistema de teste de algoritmos de ordenacao de vetores'
	print 'autor: Eder Ruiz Maria'
	print 'email: holoturoide@gmail.com'
	print
	print 'Uso: %s [-s|-o|-h] -f [arquivo]' %argv[0]
	print 
	print 'Opcoes:'
	print '  -h, --help      mostra este help e sai'
	print '  -o <arquivo>    grava o teste em <arquivo>'
	print '  -s              mostra a saida em <stdout>'
	print '  -f <arquivo>    lista de arquivos com numeros'
	print

def print_error(erro):
	
	print
	print 'Erro com o argumento %s' %erro
	print_help()

#|=============================================|
#|  'nome' |'tempo'|    'comp'   |   'atrib'   |
#|=============================================|
#|  <nome> | tempo | comparacoes | atribuicoes |
#|=============================================|

def set_atrib(dic,x):

	dic['atrib'] = dic['atrib'] + x

def set_comp(dic,x):

	dic['comp'] = dic['comp'] + x

def set_ini(dic,nome):

	dic.clear()
	dic['nome'] = nome
	dic['tam'] = 0
	dic['comp'] = 0
	dic['atrib'] = 0
	dic['tempo'] = 0.

def troca(a,b):

	aux = a
	a = b
	b = aux

def make_est_parcial(vetor):

	L = []
	L.append(shake(vetor))
	L.append(bubble(vetor))
	L.append(selection(vetor))
	L.append(insertion(vetor))
	L.append(shell(vetor))
	L.append(merge(vetor))
	
	return L[:]


def print_estatisticas(estatisticas):

	print '\a\n\r\tanalise para %i elementos' %estatisticas[0]['tam']
	print '_____________________________________________________'
	print 'nome:     tempo: (seg)      comparacoes  atribuicoes'
	print '-----------------------------------------------------'
	for i in range(len(estatisticas)): # para cada algoritmo analisado, imprima
		aux = estatisticas[i]
		
		print '\r\t\t\t\t\t %i' %aux['atrib'],
		print '\r\t\t\t    %i' %aux['comp'],
		print '\r\t  %s' %aux['tempo'],
		print '\r%s' %aux['nome']
	print '-----------------------------------------------------'

def bubble(v):

	vetor = v[:]
	set_ini(dic,'bubble')
	tam = len(vetor)

	taux = time()
	set_atrib(dic,1); set_comp(dic,1)
	for i in range(tam-1):

		set_atrib(dic,1); set_comp(dic,1)
		for j in range(i+1,tam):
			
			set_comp(dic,1)
			if vetor[i] > vetor[j]:
				
				aux = vetor[j]
				vetor[j] = vetor[i]
				vetor[i] = aux
				set_atrib(dic,3)
	
			set_comp(dic,1); set_atrib(dic,1)
		set_comp(dic,1)
		
		set_comp(dic,1); set_atrib(dic,1)
	set_comp(dic,1)
	
	dic['tam'] = tam
	dic['tempo'] = time()-taux
	return dic.copy()

def selection(v):

	vetor = v[:]
	set_ini(dic,'selection')
	tam = len(vetor)
	
	taux = time()
	set_atrib(dic,1); set_comp(dic,1)
	for i in range(tam-1):
		
		menor = i; set_atrib(dic,1)
		
		set_atrib(dic,1); set_comp(dic,1)
		for j in range(i+1,tam):
			
			set_comp(dic,1)
			if vetor[j] < vetor[menor]:
				menor = j; set_atrib(dic,1)

			set_comp(dic,1); set_atrib(dic,1)
		set_comp(dic,1)

		aux = vetor[menor]
		vetor[menor] = vetor[i]
		vetor[i] = aux
		set_comp(dic,1)

		set_comp(dic,1); set_atrib(dic,1)
	set_comp(dic,1)

	dic['tam'] = tam
	dic['tempo'] = time() - taux
	return dic.copy()

def insertion(v):

	vetor = v[:]
	set_ini(dic,'insertion')
	tam = len(vetor)

	taux = time()
	set_comp(dic,1); set_atrib(dic,1)
	for j in range(1,tam):

		chave = vetor[j]
		i = j-1
		set_atrib(dic,2)
		
		
		while i >= 0 and vetor[i] > chave:
			set_comp(dic,2)
			
			vetor[i+1] = vetor[i]
			i = i-1
			set_atrib(dic,2)
		
		if i < 0:
			set_comp(dic,1)
		else:
			set_comp(dic,2)

		vetor[i+1] = chave; set_atrib(dic,1)

		set_comp(dic,1); set_atrib(dic,1)
	set_comp(dic,1)

	dic['tam'] = tam
	dic['tempo'] = time()-taux
	return dic.copy()

def shell(v):

	vetor = v[:]
	set_ini(dic,'shell')
	tam = len(vetor)
	taux = time()
	
	set_atrib(dic,1)
	m = len(vetor)/2
	
	while m >= 1:
		set_comp(dic,1)
		
		set_atrib(dic,1); set_comp(dic,1)
		for i in range(m,tam):

			aux = vetor[i]
			j = i-m
			set_atrib(dic,2)
			
			while j >= 0 and aux < vetor[j]:
				set_comp(dic,2)
				
				vetor[j+m] = vetor[j];
				j = j-m
				set_atrib(dic,2)
			
			if j < 0:
				set_comp(dic,1)
			else:
				set_comp(dic,2)
			
			vetor[j+m] = aux; set_atrib(dic,1)

			set_comp(dic,1); set_atrib(dic,1)
		set_comp(dic,1)

		m = m/2; set_atrib(dic,2)

	dic['tam'] = tam
	dic['tempo'] = time() - taux
	return dic.copy()

def shake(v):

	vetor = v[:]
	set_ini(dic,'shake')	
	tam = len(vetor)
	laux = range(1,tam-1)
	laux.reverse()
	
	taux = time()
	while True:
		set_comp(dic,1)
		
		troca = 0; set_atrib(dic,1)

		set_atrib(dic,1); set_comp(dic,1)
		for i in range(tam-1):

			set_comp(dic,1)
			if vetor[i] > vetor[i+1]:
				
				troca = 1
				aux = vetor[i]
				vetor[i] = vetor[i+1]
				vetor[i+1] = aux; set_atrib(dic,4)
			set_comp(dic,1); set_atrib(dic,1)
		set_comp(dic,1)

		set_comp(dic,1)
		if troca == 1:
			
			set_atrib(dic,1)
			troca = 0
			
			set_atrib(dic,1); set_comp(dic,1)
			for i in laux:
			
				set_comp(dic,1)
				if vetor[i] < vetor[i-1]:

					troca = 1
					aux = vetor[i]
					vetor[i] = vetor[i-1]
					vetor[i-1] = aux; set_atrib(dic,4)
				set_comp(dic,1); set_atrib(dic,1)
			set_comp(dic,1)
		
		set_comp(dic,1)
		if troca == 0:
			break

	dic['tempo'] = time() - taux
	dic['tam'] = tam
	return dic.copy()

def intercala_tabajara (dic,v,ini,meio,fim):

	a1 = v[ini:meio+1]
	a1 += v[meio+1:fim+1]
	a1.sort()
	v[ini:fim+1] = a1

def intercala(div,v,ini,meio,fim):

	a_ini = ini#; print a_ini,
	a_fim = meio#; print a_fim,
	b_ini = meio+1#; print b_ini,
	b_fim = fim#; print b_fim
	temp = []
#	print v[a_ini:a_fim+1],
#	print v[b_ini:b_fim+1]
#	pdb.set_trace()
	while a_ini <= a_fim and b_ini <= b_fim:

		if v[a_ini] <= v[b_ini]:
			print v[a_ini]
			temp.append(v[a_ini])
			a_ini += 1
		else:
			print v[b_ini]
			temp.append(v[b_ini])
			b_ini += 1
			
	if b_ini <= b_fim:
		while b_ini <= b_fim:
			print v[b_ini]
			temp.append(v[b_ini])
			b_ini += 1
	else:
		while a_ini <= a_fim:
			print v[a_ini]
			temp.append(v[a_ini])
			a_ini += 1
	
#	print temp
#	print v

#	v[ini:fim+1] += temp
	i = ini
	while i < fim:
		v[i] = temp[i-ini]
		i += 1
		

def mergesort(dic,vetor,ini,fim):

	set_comp(dic,1)
	if ini < fim:
		meio = (ini+fim)/2 ; set_atrib(dic,1)
		mergesort(dic,vetor,ini,meio)
		mergesort(dic,vetor,meio+1,fim)
		intercala_tabajara(dic,vetor,ini,meio,fim)

def merge(v):

	vetor = v[:]
	set_ini(dic,'merge')	
	taux = time()
#	print vetor	
	mergesort(dic,vetor,0,len(vetor)-1)
#	print vetor
	dic['tempo'] = time() - taux
	dic['tam'] = len(v)
	return dic.copy()

def make_analise(nomes,to_print):
		
	est_total = []
	for nome_de_arquivo in nomes:
		
		vetor = load_file(nome_de_arquivo)
		est_parcial = make_est_parcial(vetor)

		if to_print == True:
			print_estatisticas(est_parcial)
		
		est_total.append(est_parcial)

	
#	taux = time()
#	vetor.sort()
#	print time() - taux
	return est_total[:]

if __name__ == '__main__':

#|=================================|
#| -s     | -o        | -f         |
#|=================================|
#| T or F | <arquivo> | <arquivo>  |
#|=================================|
	dic = {}
	if ('-h' in argv and len(argv) == 2) or len(argv) == 1:
		print_help()
	elif '-h' in argv:
		print_error('-h')
	else:
		if '-s' in argv:
			dic['-s'] = True
		else:
			dic['-s'] = False
		if '-o' in argv:
			dic['-o'] = argv[argv.index('-o')+1] #arquivo onde sera escrito 
		if '-f' in argv and argv.index('-f') < len(argv) -1:
			dic['-f'] = argv[argv.index('-f')+1:] #lista de arquivos a serem analisados
		else:
			print_error('-f')


	if dic.has_key('-f'):
	
		est = make_analise(dic['-f'],dic['-s'])
#		if dic.has_key('-o'):
#			escreve tudo em tal arquivo

#	try:
#		import psyco
#		psyco.profile()
#	except:
#	     print 'Psyco not found, ignoring it'


#|======================================================================
#|  e      |  est         | 'nome' | 'tam' | 'tempo' | 'comp' | 'atrib' |
#|  s      |          [0] |=============================================|
#|  t      | parcial      |  <str> | <int> | <float> |  <int> |  <int>  |
#|     [0] |          ====|=============================================
#|  t      |              |
#|  o      |          [1] |
#|  t      |              |
#|  a   ===|==============
#|  l      |
#|         |
#
# est total:   estatisticas de todos os arquivos (<list>)
# est parcial: estatisticas de todos algoritmos para um arquivo (<list>)
# 
		



# para cada arquivo
#	carregar o arquivo para o vetor
#	para cada algoritmo
#		aplica algoritmo
# 		guarda estatisticas de cada algoritmo
#	gera estatisticas do algoritmo
# gera relatorio final
# termino porra!













