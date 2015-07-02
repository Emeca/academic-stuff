%{
#include <stdio.h>
%}

%%
[0123456789]+        printf("NUMERO\n");
[a-zA-Z][a-zA-Z0-9]* printf("PALAVRA\n");
%%
