%{
  #include<string.h>
  int type=0, line=1;
  struct variable {
    char type[100], name[100], value[100];
  };
  struct variable vars[100];
  int count=0;
%}
space [\t\r]+
identifier [a-zA-Z][a-zA-Z0-9]*
intconst [\-]?[0-9]+
floatconst [\-]?[0-9]+[\.][0-9]*
operators [\-+*/%]
charconst ['].?[']
stringconst ["].*["]
special [(){},#]
keyword (do|while|for|if|else|switch|case|continue|break|main|struct|include)
logical (&&|\|\||!)
relational (>|<|>=|<=|==|!=)
assign =
comment (\/\*(.|\n)*\*\/|\/\/.*)

%%
space {printf("WH");}
\n {printf("\n%d ", line);
  line++;}
; {printf("SP ");
      type=0;}
int {printf("KW ");
      type=1;}
float {printf("KW ");
      type=2;}
char {printf("KW ");
      type=3;}
{keyword} {printf("KW ");}
{identifier} {printf("ID ");
strcpy(vars[count].name, yytext);
switch(type) {
    case 1: strcpy(vars[count].type, "int");
            vars[count].type[3]='\0';
            vars[count].value[0]='\0';
            count++;
            break;
    case 2: strcpy(vars[count].type, "float");
            vars[count].type[5]='\0';
            vars[count].value[0]='\0';
            count++;
            break;
    case 3: strcpy(vars[count].type, "char");
            vars[count].type[4]='\0';
            vars[count].value[0]='\0';
            count++;
            break;
    default: break;
}
}
{comment} {}
{assign} {printf("ASSIGN ");}
{operators} {printf("ARITHOP ");}
{intconst} {printf("INTCONST ");
          strcpy(vars[count-1].value, yytext);}
{floatconst} {printf("FLOATCONST ");
          strcpy(vars[count-1].value, yytext);}
{charconst} {printf("CHARCONST ");
          strcpy(vars[count-1].value, yytext);}
{stringconst} {printf("STRINGCONST ");}
{special} {printf("SP ");}
{logical} {printf("LOGOP ");}
{relational} {printf("RELOP ");}
%%
int main(int argc, char **argv)
{
FILE *fp; fp=fopen("sample.txt","r");
char c = fgetc(fp);
while (c != EOF) {
  printf ("%c", c);
  c = fgetc(fp);
}
fp=fopen("sample.txt","r");
yyin=fp;
printf("%d ", line);
line++;
yylex();
int i;
printf("\nType\tID\tValue\n");
for(i=0;i<count;i++) {
  printf("%s\t%s\t%s\n", vars[i].type, vars[i].name, vars[i].value);
}
return 0;
}
int yywrap() {
return 1; }
