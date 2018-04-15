%{
  #include<stdio.h>
  #include<stdlib.h>
  #include "y.tab.h"
%}
NUM [0-9]+
symbol [\-+*/%\^()]
%%
{NUM} {
        yylval=atoi(yytext);
        return NUM;}
{symbol} {return *yytext;}
\n {return *yytext;}
%%
