%{
#include "y.tab.h"
#include<stdlib.h>
%}
%%
[0-9]+ {yylval = atoi(yytext); return NUMBER;}
[\t\n] ;
"+" return(PLUS);
"-" return(MINUS);
"*" return(TIMES);
"/" return(DIVIDE);
"^" return(POWER);
";" return(END);
%%
int yywrap (void)
{return 1;}
