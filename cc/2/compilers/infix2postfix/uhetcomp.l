%option noyywrap
%option nounput

%{
#include <stdio.h>
#include <stdlib.h>
#include "uhetcomp.tab.h"

#define YY_NO_INPUT
%}

INT ([1-9]+[0-9]*)|[0]

%%

{INT}[\.][0-9]+([e]?(\+|\-)?([1-9]+)[0]*)? {
	strcpy(yylval.Num, yytext);
	return FLOAT;
}

{INT} {
	strcpy(yylval.Num, yytext);
	return INT;
}

[A-Z]{1}(\_)?([0-9]*(\_)?[a-z]*(\_)?) {
	strcpy(yylval.Var, yytext);
	return VAR;
}

[mM][oO][sS][tT][rR][aA] {
	return SHOW;
}

[sS][Qq][Rr][Tt] {
	return SQRT;
}

[=] {
	return ASSIGN;
}

[uU][hH][eE][tT] {
	printf("uuuuhhhhheeeeettttt!!!\n");
}

[cC][lL][eE][aA][rR] {
	system ("clear");
}

[ \t\n]+ {
	/* nada */
	return yytext[0];
}

%%
