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
		/* Janelas necessárias das interface */
		CDKSCREEN *cdk_tela;
		WINDOW *curses_tela;
		
		/* Entrada de texto */
		CDKMENTRY *cdk_entrada;

		/* Lista com as palavras erradas */
		CDKSCROLL *cdk_palavras;
		int npalavras;

		/* Lista com as correções das palavras */
		vector<CDKSCROLL *> cdk_escolhas;

		/* Dialog com as opções do usuário */
		CDKDIALOG *cdk_pergunta;

		/* Arquivo de log */
		ofstream *f;

		void tokenize(const string &str, vector<string> &tokens,
					  const string &delimiters);

	public:

		/*
		 * Inicia as variáveis e desenha a interface do usuário na tela
		 */
		Interface(string logfile);

		/*
		 * Desaloca as variáveis e fecha a interface
		 */
		~Interface();

		/*
		 * lê o texto de entrada do usuário e devolve um vector de strings, com
		 * cada posição sendo uma palavra do texto
		 */
		void lerEntrada(vector<string> &vEntrada);

		/*
		 * indica que a palavra passada como parametro foi
		 * reconhecida corretamente, sendo feito o log disto
		 */
		void palavraCerta(string palavra);

		/*
		 * indica que a palavra passada como parametro não foi reconhecida e
		 * escolhas são todas as possíveis correções desta palavra
		 */
		void palavraErrada(string palavra, vector<string> escolhas);

		/*
		 * passa o controle da interface para o usuário perguntando qual são as
		 * possíveis correções para a palavra atual. Se o retorno for:
		 * - 0: a palavra foi substituída, nada a fazer
		 * - 1: a palavra foi adicionada no dicionário, a variavel 'add' deve
		 *      ser inserida na arvore.
		 * - 2: o usuario cancelou o pedido, nada a fazer
		 * - 3: o usuário pediu para sair do programa, sair
		 */
		int lerEscolha(string &add);
};

#endif /* _INTERFACE_H */
