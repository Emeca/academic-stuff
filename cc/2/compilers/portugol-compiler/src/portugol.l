%option nounput noyywrap

%{
#include <stdio.h>
#include <string.h>
#include "portugol.bison.h"

int nlines = 1;
extern void yyerror (const char *);

void copy(char destino[], char origem[]){
	
	for ( int i = 0 ; i < 30 ; i++) destino[i] = '\0';
	strncpy (yylval.STR, yytext, 30);
}

%}

ESPACO			[\ \t]+
LINHA			\n

VERDADEIRO		"verdadeiro"|"Verdadeiro"|"VERDADEIRO"
FALSO			"falso"|"Falso"|"FALSO"

FUNCAO			"Funcao"|"FunÁ„o"|"funcao"|"funÁ„o"
PROCEDIMENTO	"Procedimento"|"procedimento"

ALGORITMO		"algoritmo"|"Algoritmo"|"ALGORITMO"
DECLARE			"declare"|"Declare"|"DECLARE"
MATRIZ			"matriz"|"Matriz"|"MATRIZ"
DE				"de"|"De"|"DE"

T_INTEIRO		"inteiro"|"Inteiro"|"INTEIRO"
T_REAL			"real"|"Real"|"REAL"
T_BOOLEANO		"booleano"|"Booleano"|"BOOLEANO"
T_CARACTERE		"caractere"|"Caractere"|"CARACTERE"|"caracter"|"Caracter"|"CARACTER"

REFERENCIA		"ref"|"Ref"|"REF"|"referÎncia"|"ReferÎncia"|"REFERÀNCIA"

INICIO			"inÌcio"|"InÌcio"|"INÕCIO"|"inicio"|"Inicio"|"INICIO"
FIM				"fim"|"Fim"|"FIM"

SE				"se"|"Se"|"SE"
ENTAO			"ent„o"|"Ent„o"|"ENT√O"|"entao"|"Entao"|"ENTAO"
SENAO			"sen„o"|"Sen„o"|"SEN√O"|"senao"|"Senao"|"SENAO"

AND				"e"|"E"
OR				"ou"|"Ou"|"OU"
NOT				"not"|"Not"|"NOT"
MOD				"mod"|"Mod"|"MOD"
DIV				"div"|"Div"|"DIV"

OP_RELACIONAL	"<"|"="|">="|"<="|"<>"
MAIOR			">"

OP_LOGICO		{AND}|{OR}

REPITA			"repita"|"Repita"|"REPITA"
ATE				"atÈ"|"AtÈ"|"AT…"|"ate"|"Ate"|"ATE"
ENQUANTO		"enquanto"|"Enquanto"|"ENQUANTO"
FACA			"faÁa"|"FaÁa"|"FA«A"|"faca"|"Faca"|"FACA"
PARA			"para"|"Para"|"PARA"

RESTO			{LETRA}+|{DIGITO}+|['_']+
IDENTIFICADOR	{LETRA}{RESTO}*|['_']{RESTO}+

LETRAMIN		[a-z·ÈÌÛ˙„ıÒ‡ËÏÚ˘‚ÍÓÙ˚Á]
LETRAMAI		[A-Z¡…Õ”⁄√’—¿»Ã“Ÿ¬ Œ‘‘«]
LETRA			{LETRAMIN}|{LETRAMAI}

DIGITO			[0-9]
NUMERAL			{DIGITO}+
INTEIRO			[\+\-]?{NUMERAL}
NUMERO			{INTEIRO}['.']{NUMERAL}

LITERAL			\'.*\'

PONTO			"."
PONTOPONTO		".."
DOISPONTO		":"
PONTOVIRG		";"
VIRGULA			","
ATTRIB			":="
ABRECOLCH		"["
FECHACOLCH		"]"
ABREPAR			"("
FECHAPAR		")"
ABRECHAVE		"{"
FECHACHAVE		"}"
COMENTARIO		"//"

MAIS			"+"
MENOS			"-"
VEZES			"*"
DIVID			"/"


%%


{ESPACO}			{  }
{LINHA}				{ nlines++; }

{ABRECHAVE}	{
	register int c;

	for (;;) {
		while ( ((c = yyinput()) != '}') && (c != EOF) )
			if (c == '\n') nlines++;

		if (c == '}') break;
		if (c == EOF) {
			yyerror("Coment·rio n„o terminado.");
			exit(1);
		}
	}
}

{COMENTARIO} {
	register int c;

	while ( ((c = yyinput()) != '\n') && (c != EOF) );

	if (c == EOF) {
		yyerror("Coment·rio n„o terminado!");
		exit(1);
	}
		
	nlines++;
}

{VERDADEIRO}		{ return VERDADEIRO; 	}
{FALSO}				{ return FALSO; 		}

{FUNCAO}			{ return FUNCAO; 		}
{PROCEDIMENTO}		{ return PROCEDIMENTO;	}

{ALGORITMO}			{ return ALGORITMO; 	}
{DECLARE}			{ return DECLARE; 		}
{MATRIZ}			{ return MATRIZ;		}
{DE}				{ return DE; 			}

{T_INTEIRO}			{ return T_INTEIRO;		}
{T_REAL}			{ return T_REAL;		}
{T_BOOLEANO}		{ return T_BOOLEANO;	}
{T_CARACTERE}		{ return T_CARACTERE;	}

{REFERENCIA}		{ return REFERENCIA;	}

{INICIO}			{ return INICIO;		} 
{FIM}				{ return FIM; 			}

{SE}				{ return SE;			}
{ENTAO}				{ return ENTAO;			}
{SENAO}				{ return SENAO;			}

{NOT}				{ return NOT;			}
{MOD}				{ return MOD;			}
{DIV}				{ return DIV;			}

{OP_RELACIONAL}		{ copy(yylval.STR, yytext); return OP_RELACIONAL; }
{MAIOR}				{ return MAIOR;			}
{OP_LOGICO}			{ return OP_LOGICO; 	}

{REPITA}			{ return REPITA;		}
{ATE}				{ return ATE;			}
{ENQUANTO}			{ return ENQUANTO;		}
{FACA}				{ return FACA;			}
{PARA}				{ return PARA; 			}

{IDENTIFICADOR}		{ copy(yylval.STR, yytext); return IDENTIFICADOR; }

{INTEIRO}			{ copy(yylval.STR, yytext); return INTEIRO;	}
{NUMERO}			{ copy(yylval.STR, yytext); return NUMERO; }

{LITERAL}			{ return LITERAL;		}

{PONTO}				{ return PONTO;			}
{PONTOPONTO}		{ return PONTOPONTO;	}
{DOISPONTO}			{ return DOISPONTO;		}
{PONTOVIRG}			{ return PONTOVIRG;		}
{VIRGULA}			{ return VIRGULA;		}
{ATTRIB}			{ return ATTRIB;		}
{ABRECOLCH}			{ return ABRECOLCH;		}
{FECHACOLCH}		{ return FECHACOLCH;	}
{ABREPAR}			{ return ABREPAR;		}
{FECHAPAR}			{ return FECHAPAR;		}

{MAIS}				{ return MAIS;			}
{MENOS}				{ return MENOS;			}
{VEZES}				{ return VEZES;			}
{DIVID}				{ return DIVID;			}

.					{ printf("Token %s descnhecido.\n", yytext); }


%%
