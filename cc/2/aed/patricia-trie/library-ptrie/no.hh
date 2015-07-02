#ifndef _NO_HH
#define _NO_HH

#include "include.hh"

using namespace std;

class No
{
	private:
		Tlista *subarvore;
		string *radical;

	public:
		/* cria um no vazio...OK */
		No();						

		/* cria um no setando o radical para value...OK */
		No(string value);

		~No();

		/* seta o radical do objeto com a string value...OK */
		void setRadical(string value);

		/* retorna o radical contido no objeto...OK */
		string getRadical();

		/* adiciona um no a subarvore...OK */
		void addSubarvore(No * novono);

		/* imprime os radicais da subarvore...OK */
		void printSubarvore();

		/* limpa as subarvores */
		void clear();

		/* retorna true e o no (tanto radical quanto lista) estiver vaziu */
		bool isEmpty();

		/* retorna true se o radical do no estiver vaziu */
		bool isRadicalEmpty();
		
		bool isListaEmpty();
		
		bool isFilhoVaziu();

		/* retorna um ponteiro para o no atual...OK */
		No *clone();

		/* retorna No* para um no cujo radical comece com letra...OK */
		No *getNo(const char letra);
		
		void delRadical();
		
		void delSublista();

		Tlista *getSubarvore();
};

#endif
