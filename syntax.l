%{
#include "y.tab.h"
#include<stdio.h>
#include<stdlib.h>
%}

ID [a-zA-Z][a-zA-Z0-9]*
NUM ([0-9](\.[0-9]+)?+)
OP (&&|\|\||!|\+|\-|\*|\/)
KW (int|float|char)
IF (if)
ELSE (else)
WHILE (while)
RELOP (>|<|>=|<=|==|!=)
%%
{KW} {return KW;}
{IF} {return IF;}
{WHILE} {return WHILE;}
{ELSE} {return ELSE;}
{RELOP} {return RELOP;}
{ID} {return ID;}
{NUM} {return NUM;}
{OP} {return OP;}
= {return *yytext;}
\n {return *yytext;}
, {return *yytext;}
[(){}] {return *yytext;}
%%
