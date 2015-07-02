/* vim: set sw=4 ts=4 : */

#ifndef _CALCULADORA_H
#define _CALCULADORA_H

#include <stack>
#include <list>
#include <string>
#include <math.h>
#include <stdlib.h>

using namespace std;

class Base
{
	private:
		float *valor;

	public:
		Base();
		Base(float _valor);
		float *getValor();
		void setValor(float _valor);
		~Base();
};

class Numero : public Base
{
	public:
		Numero();
		Numero(float _valor);
		~Numero();
};

class Variavel : public Base
{
	private:
		string * nome;

	public:
		Variavel();
		Variavel(string _nome);
		Variavel(char *_nome);
		Variavel(string _nome, float _valor);

		string getNome();
		void setNome(string _nome);

		~Variavel();
};

class Calculadora : public yyFlexLexer
{
	private:
		stack < Numero * >*pilha;
		list < Variavel * >*var;
		/* se variavel existir retorna um ponteiro para ela, se nao retorna NULL */
		Variavel *getPointerVar(string _nome);
		void error(string erro);
		float divisao(float, float);

	public:
		Calculadora();

		void echo(string s);
		void printVar();

		void inteiro();
		void real();
		void variavel();

		void operador();

		void raiz();
		void igual();

		~Calculadora();
};

Base::Base()
{
	valor = NULL;
}

Base::Base(float _valor)
{
	valor = new float (_valor);
}

float *
Base::getValor()
{
	if (valor) {
		float *f = new float (*valor);
		return f;
	}
	return NULL;
}

void
Base::setValor(float _valor)
{
	if (valor)
		delete(valor);
	valor = new float(_valor);
}

Base::~Base()
{
	delete(valor);
}

Numero::Numero(float _valor):
Base(_valor)
{
}

Variavel::Variavel(string _nome) : Base()
{

	nome = new string(_nome);
}

Variavel::Variavel(char *_nome):
Base()
{

	nome = new string(_nome);
}

Variavel::Variavel(string _nome, float _valor) : Base(_valor)
{
	nome = new string(_nome);
}

void
Variavel::setNome(string _nome)
{
	if (nome)
		delete(nome);
	nome = new string(_nome);
}

string
Variavel::getNome()
{
	return *nome;
}

Variavel::~Variavel()
{
	delete(nome);
}

void
Calculadora::error(string erro)
{
	cout << "\r" << erro << endl;
}

Calculadora::Calculadora()
{
	pilha = new stack < Numero * >();
	var = new list < Variavel * >();
}

void
Calculadora::echo(string s)
{
	cout << yytext << s << endl;
}

Calculadora::~Calculadora()
{
	delete(pilha);
	delete(var);
}

void
Calculadora::inteiro()
{
	Numero *aux = new Numero(atof(yytext));
	pilha->push(aux);
}

void
Calculadora::real()
{
	Numero *aux = new Numero(atof(yytext));
	pilha->push(aux);
}

float
Calculadora::divisao(float dois, float um)
{
	if (um != 0)
		return dois / um;
	error("Divisao por Zero :`(");
	Numero *aux = new Numero(dois);
	pilha->push(aux);
	return um;
}

void
Calculadora::operador()
{
	if (!pilha->empty()) {

		float um = *pilha->top()->getValor();
		pilha->pop();
		if (!pilha->empty()) {
			float dois = *pilha->top()->getValor();
			pilha->pop();
			float result;
			switch (yytext[0]) {
			case '+':
				result = dois + um;
				break;
			case '-':
				result = dois - um;
				break;
			case '*':
				result = dois * um;
				break;
			case '/':
				result = divisao(dois, um);
				break;
			case '^':
				result = powf(dois, um);
				break;
			}
			Numero *aux = new Numero(result);
			pilha->push(aux);
			cout << "\r" << result << endl;
		} else {
			error("Apenas um Operador na Pilha :`(");
			Numero *aux = new Numero(um);
			pilha->push(aux);
		}
	} else
		error("Pilha Vazia :`(");
}

void
Calculadora::raiz()
{
	if (!pilha->empty()) {
		float um = *pilha->top()->getValor();
		pilha->pop();
		if (um >= 0) {
			um = sqrt(um);
			cout << "\r" << um << endl;
		} else
			error("Nao Consigo Calcular Raiz de Numero Negativo :`(");

		Numero *aux = new Numero(um);
		pilha->push(aux);
	} else
		error("Pilha Vazia :`(");
}

Variavel *
Calculadora::getPointerVar(string _nome)
{
	list <Variavel *>::iterator it = var->begin();
	Variavel *v_aux;

	while (it != var->end()) {

		v_aux = *it;
		if (_nome == v_aux->getNome())
			return v_aux;
		it++;
	}
	return NULL;
}

void
Calculadora::igual()
{
	if (!pilha->empty()) {
		float aux = *pilha->top()->getValor();
		pilha->pop();
		cout << "\r" << aux << endl;
	} else
		error("Pilha Vazia :`(");
}

void
Calculadora::variavel()
{
	Variavel *vaux = getPointerVar(yytext);

	if (vaux == NULL) {

		if (!pilha->empty()) {
			vaux = new Variavel(yytext, *pilha->top()->getValor());
			var->push_front(vaux);
		} else
			error("Pilha Vazia :`(");

	} else {
		Numero *num = new Numero(*vaux->getValor());
		pilha->push(num);
	}
}

void
Calculadora::printVar()
{
	list <Variavel *>::iterator it = var->begin();
	Variavel *aux = NULL;

	cout << "Imprimindo as Variaveis: " << endl;
	for (; it != var->end(); it++) {

		aux = *it;
		cout << "\r" << aux->getNome() << "(" << *aux->	getValor() << ")\n";
	}
}

#endif
