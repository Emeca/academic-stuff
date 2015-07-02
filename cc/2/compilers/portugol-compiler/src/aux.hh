#ifndef _AUX_HH
#define _AUX_HH

#include <list>
#include <string>
#include <iostream>
#include <stdlib.h>

#define _VOID 0
#define _INT 1
#define _FLOAT 2
#define _BOOL 3
#define _CHAR 4

#define _USADO 0
#define _LIVRE 1
#define _PARCIAL 2

#define _MAIS_ 20
#define _MENOS_ 21
#define _VEZES_ 22
#define _DIVIDIR_ 23
#define _MOD_ 24
#define _DIV_ 25
#define _MAIOR_ 26
#define _ATRIBUICAO_ 27

#define _INTEIRO_ 30
#define _VARIAVEL_ 31

using namespace std;

extern int nlines;

class Variaveis:public list<string>{

	public:
		void print();
};

class Exp {

	private:
		string token;
		int tipo;
	
	public:
		Exp();
		Exp(string _token, int _tipo);
		Exp(const char _token[], int _tipo);
		string getToken();
		int getTipo();
		Exp* getCopy();
		void print();
		~Exp();
};

class Expressao:public list<Exp> {

	public:
		void print();
};


class Array {

	private:
		int sub_ini;
		int sub_fim;
		int tam;
	public:
		Array();
		Array(int ini, int fim, int n);
		int getIni();
		int getFim();
		int getTam();
		Array* get();
		~Array();
};

class Tipo {
	
	private:
		int tipo;
		Array* matriz;
	public:
		Tipo();
		Tipo(int _tipo);
		Tipo(int _tipo, Array* _matriz);
		void setTipo(int _tipo);
		void setArray(Array* _matriz);
		Array* getArray();
		Tipo* get();
		int getTipo();
		~Tipo();
};

class Simbolo {

	private:
		string* nome;
		Tipo* tipo;
		bool inicializada;
	public:
		Simbolo();
		Simbolo(string _nome, Tipo _tipo, bool ini);
		void setNome(string _nome);
		void setTipo(Tipo _tipo);
		void setIni(bool flag);
		bool getIni();
		string* getNome();
		Tipo* getTipo();
		void print();
		~Simbolo();
};

class TSimbolo:public list<Simbolo*> {

	public:
		void print();
		bool existe(string _nome);
		Simbolo* getSimbolo(string _nome);
		void atualiza(Simbolo* sim);
};

class Codigo {

	private:
		void make_conta(string inst, int op);
			
	public:
		Codigo();
		void expressao(Expressao* exp);
		void atribuicao(string var);
		void declara(TSimbolo* table);
	
		void se(string label);
		void exp_relacional(Expressao* exp, string label);
		void fim(string label);
		void jmp(string label);
		~Codigo();
};

class Registrador {

	private:
		string nome;
		unsigned int h;
		unsigned int l;

	public:
		Registrador();
		void setH(unsigned int status);
		void setL(unsigned int status);
		void setF(unsigned int status);
		unsigned int getH();
		unsigned int getL();
		unsigned int getF();
		void setNome(string s);
		string getNome();
};

class Pilha:public list<Exp>{

	public:	
		void print();	
};


class Processador {

	private:
		Registrador reg[4];
		Pilha* pilha;
		
	public:
		Processador();
		void setStatus(string reg, unsigned int _status);
		unsigned int getStatus(string reg);
		string getLivre();
		Pilha* getPilha();
		~Processador();
};	


#endif
