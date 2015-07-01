%{
#include <stdio.h>

#define YYERROR_VERBOSE
#define YYDEBUG 1

int yylex();
int yyerror(const char *s);
%}

%union {
	char Var[32];
	char Num[50];
	
}

%token <Num> FLOAT INT
%token <Var> VAR

%token SHOW SQRT ASSIGN

%start input

%right '='
%left  '+' '-'
%left  '*' '/'
%right '^'

%%

input: /* vazio */
	| input exp				{ printf("\n");}
	| input VAR ASSIGN exp 	{ printf("%s \n", $<Var>2); }
;

exp:  FLOAT				{ printf("%s ", $<Num>1); }
	| INT				{ printf("%s ", $<Num>1); }
	| VAR				{ printf("%s ", $<Var>1); }
	| SQRT '(' exp ')'	{ printf("sqrt "); }
	| SHOW VAR			{ printf("= %s ", $2); }
	| exp '+' exp		{ printf("+ "); }
	| exp '-' exp		{ printf("- "); }
	| exp '*' exp		{ printf("* "); }
	| exp '/' exp		{ printf("/ "); }
	| exp '^' exp		{ printf("^ "); }
	| '(' exp ')'		{ }
;

%%


/* secao de subrotinas */
int
yyerror (const char* s)
{
	fprintf(stderr, "%s\n", s);
	return 0;
}

int
main(void)
{
	yyparse();
	return 0;
}
