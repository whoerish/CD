#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char data[1000][1000];
int numStatements, vars[26], counter=0;
int main(int argc, char const *argv[]) {
  printf("\nEnter the number of statements :");
  scanf("%d", &numStatements);
  int i;
  gets(data[0]);
  for(i=0;i<numStatements;i++) {
    gets(data[i]);
  }
  for(i=0;i<26;i++) {
    vars[i]=-1;
  }
  for(i=0;i<numStatements;i++) {
    int state=0;
    int j=0;
    int rhs, op1, op2;
    char rhsvar, op1var=-1;
    int assign=0;
    char operator;

    if(isupper(data[i][0])) {
      printf("\n%.2s :", data[i]);
      j=3;
    }


    char *c=strstr(data[i], "goto");
    if(c!=NULL) {
      if(c==data[i]) {
        printf("\nJMP %s", data[i]+4);
        continue;
      }

    }
    c=strstr(data[i], "stop");
    if(c!=NULL) {
      printf("\nHALT");
      continue;
    }


    c=strstr(data[i], "if");
    if(c!=NULL) {
      int start=c-data[i]+2;

      j+=3;


      while (1) {
          if(state==0) {
          char num[100]; int k=0;
          if(isalpha(data[i][j])) {
            if(vars[data[i][j]-'a']==-1) {
              vars[data[i][j]-'a']=counter++;
              printf("\nMOV R%d, %c", vars[data[i][j]-'a'], data[i][j]);
            }
            op1=vars[data[i][j]-'a'];

            j++;
          }
          else if(isdigit(data[i][j])) {
            op1=counter++;
            while (isdigit(data[i][j])) {
              num[k++]=data[i][j];
              j++;
            }
            j--;
            num[k]='\0';
            printf("\nMOV R%d, #%s", op1, num);
          }

          while (!isalnum(data[i][j])) {
            j++;
          }
          j--;
          state=1;
        }
        else if(state==1) {

          if(isalpha(data[i][j])) {
            if(vars[data[i][j]-'a']==-1) {
              vars[data[i][j]-'a']=counter++;
              printf("\nMOV R%d, %c", vars[data[i][j]-'a'], data[i][j]);
            }
            op2=vars[data[i][j]-'a'];
          }
          else if(isdigit(data[i][j])) {
            op2=counter++;
            printf("\nMOV R%d, #", op2);
            while (isdigit(data[i][j])) {
              printf("%c", data[i][j]);
              j++;
            }
            j--;
          }
          state=2;
        }

        if(state==2) {
          printf("\nCMP R%d R%d", op1, op2);
          if(strstr(data[i], "<=")!=NULL) {
            char *temp=strstr(data[i], "goto");
            printf("\nJLE %s", temp+4);
          }
          else if(strstr(data[i], ">=")!=NULL) {
            char *temp=strstr(data[i], "goto");
            printf("\nJGE %s", temp+4);
          }
          break;
        }

        j++;
      }


      continue;
    }



    while (1) {

      if(state==0) {
       /* if(vars[data[i][j]-'a']==-1) {
          vars[data[i][j]-'a']=counter++;
        }
        rhs=vars[data[i][j]-'a'];*/
        rhsvar=data[i][j];
        state=1;
        j++;
      }

      else if(state==1) {
        char num[100]; int k=0;
        if(isalpha(data[i][j])) {
          if(vars[data[i][j]-'a']==-1) {
            vars[data[i][j]-'a']=counter++;
            printf("\nMOV R%d, %c", vars[data[i][j]-'a'], data[i][j]);
          }
          op1=vars[data[i][j]-'a'];
          op1var=data[i][j];
          j++;
          operator=data[i][j];
          if(operator=='\0') {
            printf("\nMOV %c, R%d", rhsvar, op1);
            assign=1;
            state=3;
          }
          else
            state=2;
        }
        else if(isdigit(data[i][j])) {



          while (isdigit(data[i][j])) {
            num[k++]=data[i][j];
            j++;
          }
          operator=data[i][j];
          num[k]='\0';

          if(operator=='\0') {
            if(vars[rhsvar-'a']==-1)
                vars[rhsvar-'a']=counter++;
            rhs=vars[rhsvar-'a'];
            printf("\nMOV R%d, #%s", rhs, num);
            state=3;
            assign=1;
          }
          else {
            op1=counter++;
            printf("\nMOV R%d, #%s", op1, num);
            state=2;
          }
        }

      }
      else if(state==2) {
        if(isalpha(data[i][j])) {
          if(vars[data[i][j]-'a']==-1) {
            vars[data[i][j]-'a']=counter++;
            printf("\nMOV R%d, %c", vars[data[i][j]-'a'], data[i][j]);
          }
          op2=vars[data[i][j]-'a'];
        }
        else if(isdigit(data[i][j])) {
          op2=counter++;
          printf("\nMOV R%d, #", op2);
          while (isdigit(data[i][j])) {
            printf("%c", data[i][j]);
            j++;
          }
          j--;
        }
        state=3;
      }

      if(state==3) {
        if(assign) {

        }
        else {
          switch (operator) {
            case '+': printf("\nADD R%d R%d", op1, op2);
                      break;
            case '-': printf("\nSUB R%d R%d", op1, op2);
                      break;
            case '*': printf("\nMUL R%d R%d", op1, op2);
                      break;
            case '/': printf("\nDIV R%d R%d", op1, op2);
                      break;
          }
          if(op1var!=-1) {
            vars[rhsvar-'a']=vars[op1var-'a'];
            printf("\nMOV %c, R%d", rhsvar, op1);
            vars[op1var-'a']=-1;
          }
        }
        break;
      }

      j++;
    }
  }

  return 0;
}
