%{
  #include "y.tab.h"
  #include<stdio.h>
  #include<math.h>
  #include<stdlib.h>
%}

%token OP
%token ID NUM KW IF ELSE RELOP WHILE


%%
S: S ASEXP '\n'
    |
   S DECEXP '\n'
    |
  S CONDEXP '\n'
    |
  S LOOP '\n'
    |
    ;

LOOP : WHILE '('RELEXP ')' '{' '\n' EXP '}' '\n'
      {printf("Correct\n");}


CONDEXP : IF '('RELEXP ')' '{' '\n' EXP '}' B
        {printf("Correct\n");}
B :  ELSE '{' '\n' EXP '}' '\n'| '\n';
RELEXP : ID RELOP ID | ID RELOP ID OP RELEXP;

EXP : DECEXP '\n' Q| ASEXP '\n' Q| CONDEXP '\n' Q | LOOP '\n' Q;
Q : EXP | ;

DECEXP : KW VARLIST
          {printf("Correct\n");};
VARLIST : ID VARLIST1;
VARLIST1 : ',' VARLIST | '=' NUM ',' VARLIST | '=' NUM | ;

ASEXP : ID '=' E
        {printf("Correct\n");}
        ;
E : E OP E
    |
    ID
    |
    NUM;
%%
int yywrap()
{
  return(1);
}

int main()
{
 yyparse();
 return 0;
}


yyerror( s )
char *s;
{
  printf( stderr , " Error\n");
  yyparse();
}
