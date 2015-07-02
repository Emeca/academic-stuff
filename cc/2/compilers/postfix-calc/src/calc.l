%option c++ noyywrap

%{
#include "calc.h"
	Calculadora *c;
%}

%%

([1-9][0-9]*|[0])[\.][0-9]+([e](\+|\-)[0-9]+)? { c->real(); }
[1-9]+[0]*|[0] { c->inteiro(); }
[A-Z]{1}(\_)?([0-9]*(\_)?[a-z]*(\_)?) { c->variavel(); }
[+\-*/\^] { c->operador(); }
sqrt { c->raiz(); }
= { c->igual(); }
ls { c->printVar(); }
exit|quit { exit(0); }
[ \t\n]+ 
. { cout << "Comando Invalido: " << yytext << endl;}

%%

int
main(void)
{
	c = new Calculadora(); 
	cout << "======================" << endl;
	cout << "Autores:" << endl;
	cout << "-> Andre Slompo" << endl;
	cout << "-> Eder Ruiz Maria" << endl;
	cout << "-> Rodrigo Renie Braga" << endl;
	cout << "======================" << endl;
	c->yylex();
	delete(c);
	return 0;
}


