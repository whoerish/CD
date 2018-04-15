%{

#include <stdio.h>
#include<string.h>

 typedef struct node
 {
  int type;
 } node;

 node *mknode(int type);
#define YYSTYPE struct node *
%}
%start lines
%token INTNUMBER FLOATNUMBER CHARNUMBER EQUAL
%token OP
%token END
%left EQUAL
%left PLUS
%%


lines:
 | lines line
line: exp END { switch($1->type) {
      case 1: printf("Valid Integer\n");
                break;
      case 2: printf("Valid Float\n");
                break;
      case 3: printf("Valid Char\n");
              break;
      default: printf("Not valid\n");
}}
 ;
exp : factor {$$ = $1;}
 | exp OP exp {
          if($1->type==$3->type)
              $$ = mknode($1->type);
          else if(($1->type-$3->type==1) || ($1->type-$3->type==-1))
              $$=mknode(2);
          else
              $$=mknode(4);
          }
 | exp EQUAL exp {
          if($1->type==$3->type)
              $$ = mknode($1->type);
          else if(($1->type-$3->type==1) || ($1->type-$3->type==-1))
              $$=mknode(2);
          else
              $$=mknode(4);
          }
  | '(' exp ')' {
      $$=$2;
  }
 ;

factor : INTNUMBER {$$ = mknode(1);}
          |
        FLOATNUMBER {$$ = mknode(2);}
          |
        CHARNUMBER {$$ = mknode(3);}

 ;
%%
int main (void) {return yyparse ( );}
node *mknode(int type)
{
 node *newnode = (node *)malloc(sizeof(node));
 newnode->type=type;
 return(newnode);
}

int yyerror (char *s) {fprintf (stderr, "%s\n", s);}
