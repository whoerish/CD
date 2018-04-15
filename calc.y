%{
  #include "y.tab.h"
  #include<stdio.h>
  #include<math.h>
%}

%token NUM
%left '+' '-'
%left '*' '/' '%'
%left '^'
%%
list:
        list stat '\n'
        |
        ;
stat: expr
      { printf("%d\n", $$); }
      ;
expr: '(' expr ')'
      { $$ = $2; }
      |
      expr '*' expr
      { $$=$1*$3; }
      |
      expr '+' expr
      { $$=$1+$3; }
      |
      expr '-' expr
      { $$=$1-$3; }
      |
      expr '/' expr
      { $$=$1/$3; }
      |
      expr '%' expr
      { $$=$1%$3; }
      |
      NUM
      { $$=$1; }
      ;
%%
      int yyerror()
      {
        return 0;
      }

      int yywrap()
      {
        return(1);
      }

      int main()
      {
       yyparse();
       return 0;
      }
