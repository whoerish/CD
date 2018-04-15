%{
#include "y.tab.h"
#include<stdlib.h>
%}
%%
[0-9]+ {return INTNUMBER;}
[0-9]+(\.[0-9]+)? {return FLOATNUMBER;}
[a-zA-Z] {return CHARNUMBER;}
[\t\n] ;
[\-+*/] return(OP);
"==" return(EQUAL);
";" return(END);
[()] return *yytext;
%%
int yywrap (void)
{return 1;}
