/* vim: set ts=4 sw=4:*/

#ifndef _INTERFACE_H
#define _INTERFACE_H 1

#include <iostream>
#include <vector>
#include <string>
#include <fstream>

extern "C" {
#include <cdk/cdk.h>
};

using namespace std;

class Interface
{
	private:
		/* Janelas necess�rias das interface */
		CDKSCREEN *cdk_tela;
		WINDOW *curses_tela;
		
		/* Entrada de texto */
		CDKMENTRY *cdk_entrada;

		/* Lista com as palavras erradas */
		CDKSCROLL *cdk_palavras;
		int npalavras;

		/* Lista com as corre��es das palavras */
		vector<CDKSCROLL *> cdk_escolhas;

		/* Dialog com as op��es do usu�rio */
		CDKDIALOG *cdk_pergunta;

		/* Arquivo de log */
		ofstream *f;

		void tokenize(const string &str, vector<string> &tokens,
					  const string &delimiters);

	public:

		/*
		 * Inicia as vari�veis e desenha a interface do usu�rio na tela
		 */
		Interface(string logfile);

		/*
		 * Desaloca as vari�veis e fecha a interface
		 */
		~Interface();

		/*
		 * l� o texto de entrada do usu�rio e devolve um vector de strings, com
		 * cada posi��o sendo uma palavra do texto
		 */
		void lerEntrada(vector<string> &vEntrada);

		/*
		 * indica que a palavra passada como parametro foi
		 * reconhecida corretamente, sendo feito o log disto
		 */
		void palavraCerta(string palavra);

		/*
		 * indica que a palavra passada como parametro n�o foi reconhecida e
		 * escolhas s�o todas as poss�veis corre��es desta palavra
		 */
		void palavraErrada(string palavra, vector<string> escolhas);

		/*
		 * passa o controle da interface para o usu�rio perguntando qual s�o as
		 * poss�veis corre��es para a palavra atual. Se o retorno for:
		 * - 0: a palavra foi substitu�da, nada a fazer
		 * - 1: a palavra foi adicionada no dicion�rio, a variavel 'add' deve
		 *      ser inserida na arvore.
		 * - 2: o usuario cancelou o pedido, nada a fazer
		 * - 3: o usu�rio pediu para sair do programa, sair
		 */
		int lerEscolha(string &add);
};

#endif /* _INTERFACE_H */
