%{

#include <stdio.h>
#include<string.h>

 typedef struct node
 {
 struct node *left;
 struct node *right;
 int x, flag;
 } node;

 node *mknode(node *left, node *right, int x, int flag);


#define YYSTYPE struct node *
%}
%start lines
%token NUMBER
%token PLUS MINUS TIMES DIVIDE POWER
%token END
%left PLUS MINUS
%left TIMES DIVIDE
%right POWER
%%
lines:
 | lines line
line: exp END { printf("done");}
 ;
exp : factor {$$ = $1;}
 | exp PLUS exp {$$ = mknode($1, $3, '+', 0);}
 | exp MINUS exp {$$ = mknode($1, $3, '-', 0);}
 | exp TIMES exp {$$ = mknode($1, $3, '*', 0);}
 | exp DIVIDE exp {$$ = mknode($1, $3, '/', 0);}
 ;

factor : NUMBER {$$ = mknode(0,0,(int)yylval, 1);}
 ;
%%

int main (void) {return yyparse ( );}
node *mknode(node *left, node *right, int x, int flag)
{
 node *newnode = (node *)malloc(sizeof(node));
 newnode->left = left;
 newnode->right = right;
 newnode->x = x;
 newnode->flag=flag;
 if(flag) {
  printf("\nNode %d is created at %p", x, newnode);
 }
 else {
  printf("\nNode %c is created at %p with left child at %p and right child at %p", x, newnode, newnode->left, newnode->right);
 }
 return(newnode);
}

int yyerror (char *s) {fprintf (stderr, "%s\n", s);}
