#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct variable{
  char type[100], name[100], value[100];
};

int main(int argc, char const *argv[]) {
  int state=0;
  int flag=1;
  char c;
  int type=0, count=0, exit=0;
  struct variable vars[10];
  char id[100], index1=0;
  char value[100], index2=0;


  while (1) {
    /* code */
    if(flag)
      c=getchar();
    if(flag!=2)
        flag=1;

    switch (state) {
      case 0: if(isalpha(c)) {
                state=1;
                flag=0;
              }
              if(isdigit(c)) {
                state=2;
                value[index2++]=c;
              }
              switch (c) {
                case '<':state=3;break;
                case '>':state=4;break;
                case '=':state=5;break;
                case '!':state=6;break;
                case ';':state=14;type=0;break;
                case '+':state=8;break;
                case '-':state=9;break;
                case '*':state=10;break;
                case '/':state=11;break;
                case '&':state=12;break;
                case '|':state=13;break;
                case '(':state=14;break;
                case ')':state=14;break;
                case '{':state=14;exit++;break;
                case '}':state=14;exit--;
                        if(exit==0)
                            flag=2;
                        break;
              }
              break;
       case 1:if (isdigit(c))
               state=22;  //state for identifier
             else if(c=='f')
              state=16;
             else if(c=='i')
              state=17;
             else if(c=='c')
              state=18;
             else if(c=='e')
              state=19;
             else if(c=='p')
              state=20;
             else if(c=='s')
              state=21;
             else if(c=='m')
              state=47;
             else if (c=='_')
              state=22; //identifier
             else if(!isalnum(c)) {
              state=22;
              flag=0;
            }
            id[index1++]=c;
            break;
       case 2: if(isalpha(c)) {
                state=25; //not an identifier
                index2=0;
               }
               else if(isdigit(c)) {
                state=2;
                value[index2++]=c;
               }
               else {
                value[index2]='\0';
                if(type>0) {
                    strcpy(vars[count-1].value, value);
               }
                index2=0;
                printf("CONST ");
                state=0;
                flag=0;
               }
               break;
       case 3: if(c=='='){
                printf("LE ");
                state=0;
              }
              else {
                printf("LT ");
                state=0;
                flag=0;
              }
              break;

       case 4: if(c=='=') {
                printf("GE ");
                state=0;
              }
              else {
                printf("GT ");
                state=0;
                flag=0;
              }
              break;
        case 5: if(c=='=') {
                  printf("EQ ");
                  state=0;
                }
                else {
                  printf("ASSIGN ");
                  state=0;
                  flag=0;
                }
                break;

        case 6: if(c=='=') {
                  printf("NEQ ");
                  state=0;
                }
                else {
                  printf("NOT ");
                  state=0;
                  flag=0;
                }
                break;
        case 8: if(isalnum(c)) {
                  printf("ADD ");
                  state=0;
                  flag=0;
                }
                break;
        case 9: if(isalnum(c)) {
                  printf("SUB ");
                  state=0;
                  flag=0;
                }
                break;
        case 10: if(isalnum(c)) {
                  printf("MUL ");
                  state=0;
                  flag=0;
                }
                break;
        case 11: if(isalnum(c)) {
                  printf("DIV ");
                  state=0;
                  flag=0;
                }
                else if(c=='/'){
                  printf("SLP ");
                  state=23; //single line comment
                  type=0;
                }
                else if(c=='*')
                  state=24; //multi line comment
                break;

        case 12: printf("AND ");
                  state=0;
                  break;
        case 13: printf("OR ");
                  state=0;
                  break;

        case 14: printf("SP ");
                 if(flag==2)
                    flag=3;
                 else
                    flag=0;
                 state=0;
                 break;
        case 16: if(c=='o')
                  state=26;
                 else if(c=='l')
                  state=44;
                 else {
                  state=22;
                  flag=0;
                 }
                 id[index1++]=c;
                 break;
       case 17: if(c=='f')
                  state=27;
                else if(c=='n')
                  state=28;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 18: if(c=='a')
                  state=29;
                 else if(c=='h')
                  state=30;
                 else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 19: if(c=='l')
                  state=33;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;

        case 20: if(c=='r')
                  state=35;
                 else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;

        case 21: if(c=='c')
                  state=41;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;

        case 22: while (1) {
                  if (!isalnum(c) && c!='_')
                  {
                    printf("ID ");
                    id[index1-1]='\0';
                    if(type>0)
                        strcpy(vars[count].name, id);
                    index1=0;
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
                    state=0;
                    flag=0;
                    break;
                  }
                  c=getchar();
                  id[index1++]=c;
                }
                break;
        case 23: while (1) {
                  /* code */
                  c=getchar();
                  if(c=='\n')
                  {
                    state=0;
                    break;
                  }
                }
                break;
        case 24: while (1) {
                  /* code */
                  c=getchar();
                  if(c=='/') {
                    state=0;
                    break;
                  }
                }
                break;
        case 25: while (1) {
                  c=getchar();
                  if(!isalnum(c))
                  {
                    printf("Not an ID ");
                    state=0;
                    flag=0;
                    break;
                  }
                }
                break;
        case 26:if(c=='r') {
                  state=27;
                }
                else {
                 state=22;
                 flag=0;
                }
                id[index1++]=c;
                break;
        case 27: if(isalpha(c)) {
                    state=22;
                    flag=0;
                    id[index1++]=c;
                  }
                  else {
                    printf("KW ");
                    state=0;
                    flag=0;
                    index1=0;
                  }
                  break;
        case 28: if(c=='t') {
                    type=1;
                    state=27;
                  }
                  else {
                    state=22;
                    flag=0;
                  }
                  id[index1++]=c;
                  break;
        case 29:if(c=='s')
                  state=31;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 30: if(c=='a')
                  state=32;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 31: if(c=='e')
                  state=27;
                else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 32: if(c=='r') {
                  type=3;
                  state=27;
                }
                 else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 33: if(c=='s')
                  state=34;
                 else {
                   state=22;
                   flag=0;
                 }
                 id[index1++]=c;
                 break;
        case 34: if(c=='e')
                  state=27;
                 else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 35: if(c=='i')
                  state=37;
                 else {
                  state=22;
                  flag=0;
                }
                id[index1++]=c;
                break;
        case 37: if(c=='n')
                  state=38;
                 else {
                   state=22;
                   flag=0;
                 }
                 id[index1++]=c;
                 break;
        case 38: if(c=='t')
                  state=39;
                 else {
                   state=22;
                   flag=0;
                 }
                 id[index1++]=c;
                 break;
        case 39:if(c=='f')
                  state=40;
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 40: printf("Function call ");
                 index1=0;
                 while (1) {
                    c=getchar();
                    if(c==')')
                    {
                      state=0;
                      break;
                    }
                }
                break;

        case 41:if(c=='a')
                  state=42;
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 42: if(c=='n')
                  state=43;
                 else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 43:if(c=='f')
                  state=40;
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 44:if(c=='o')
                  state=45;
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 45:if(c=='a')
                  state=46;
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 46:if(c=='t') {
                  type=2;
                  state=27;
                }
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 47:if(c=='a') {
                  state=48;
                }
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 48:if(c=='i') {
                  state=49;
                }
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;
        case 49:if(c=='n') {
                  state=27;
                }
                else {
                  flag=0;
                  state=22;
                }
                id[index1++]=c;
                break;

        default:printf("Not implemented\n");
    }
    if(c=='\n')
        printf("\n");
    if(flag==3)
      break;
  }
  int i;
  printf("\nType\tID\tValue\n");
  for(i=0;i<count;i++) {
    printf("%s\t%s\t%s\n", vars[i].type, vars[i].name, vars[i].value);
  }
  return 0;
}
