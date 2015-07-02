#ifndef _TREE_HH
#define _TREE_HH

#include "include.hh"
#include "no.hh"

class Tree
{
	private:
		unsigned tamanho;
		No *root;

		void printArvore(No *tree, unsigned nivel);

		bool consulta(string value, No *no);

		/* retorna o radical comum entre s1 e s2, s1 e s2 ficam com sufixo */
		string analise(string &s1, string &s2);

		/* insere o no na lista */
		void insere(string value, Tlista *list);

		bool consome(stack<No *> *pilha, string value, No *no);

		void chuta(No *no_inicial, stack<No *> pilha, vector<string> *vet,
				   unsigned nivel);

	public:
		Tree();

		~Tree();

		/* retora um ponteiro pra raiz */
		No *getRoot();

		/* retorna a quantidade de palavras na arvore */
		unsigned getTamanho();

		/* imprime todos radicas da arvore */
		void printArvore();

		string pilha_to_string(stack<No *> *pilha);

		stack<No *> *empilha(string value);

		vector<string> *sugestao(string value, unsigned nivel);

		void add(string value);

		bool consulta(string value);

		void deltree();

		void deltree(No * no);
};

#endif
