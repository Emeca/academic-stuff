#ifndef __MATRIZ_H
#define __MATRIZ_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define LINHAS 8
#define COLUNAS 8

#define TRUE 1
#define FALSE 0

#define TEM 1
#define NAO_TEM 0

#define RANDOM 69

#define AMARELO "\033[01;33m"
#define VERMELHO "\033[01;31m"
#define VERDE "\033[01;32m"
#define AZUL "\033[01;34m"
#define MAGENTA "\033[01;35m"
#define BRANCO "\033[01;37m"
#define PRETO "\033[01;30m"
#define NEUTRO "\033[00m"

/*
#define AMARELO ""
#define VERMELHO ""
#define VERDE ""
#define AZUL ""
#define MAGENTA ""
#define BRANCO ""
#define PRETO ""
#define NEUTRO ""
*/

/* 
     0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 
   ---------------------------------
 0 |   |   |   |   |   |   |   |   |
   ---------------------------------
 1 |   |   |   |   |   |   |   |   |
   ---------------------------------
 2 |   |   |   |   | x |   |   |   |
   ---------------------------------
 3 |   |   |   |   |   |   |   |   |
   ---------------------------------
 4 |   |   |   |   |   |   |   |   |
   ---------------------------------
 5 |   |   |   |   |   |   |   |   |
   ---------------------------------
 6 |   |   |   |   |   |   |   |   |
   ---------------------------------
 7 |   |   |   |   |   |   |   |   |
   ---------------------------------
 */

class Matriz;
class Matriz
{
	private:
		int h;
		int **m;

		int busca_linha(int lin, int col);
		int busca_coluna(int lin, int col);
		int busca_diagonal(int lin, int col);
		int come_ou_nao(int lin, int col);
		int **aloca_matriz(void);
		void desaloca_matriz(int lin);
		int tromba();

	public:
		Matriz();
		Matriz(Matriz * m);
		Matriz(int flag);
		void set(int lin, int col, int value);
		int get_pos_rainha(int lin);
		void imprime_matriz();
		void calc_h();
		int get_h();
		int **matriz_copy();
		~Matriz();
};

#endif
