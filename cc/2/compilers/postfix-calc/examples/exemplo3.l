%{
#include <stdio.h>
%}

%%
[a-zA-Z][a-zA-Z0-9]* printf("PALAVRA");
[a-zA-Z0-9\/.-]+     printf("NOME_ARQUIVO");
\"                   printf("ASPAS_DUPLAS");
\{                   printf("ABRE_CHAVES");
\}                   printf("FECHA_CHAVES");
;                    printf("PONTO_E_VIRGULA");
\n                   printf("\\n");
[ \t]+               /* ignorar espaços em branco e tabs */;
%%
