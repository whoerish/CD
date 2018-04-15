#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


struct activation_record {
  int returnAddress, numParams;
};

char data[1000][1000];
int address[1000];
int funcAddress[1000], numFunctions=0, n, endAddress, startAddress=20, curAddress;

struct activation_record stack[100];int topofStack=-1;

void push(int row) {
  int num=0, i;
  for(i=0;data[row][i]!='\0';i++) {
    if(data[row][i]==',') {
      num++;
    }
  }
  struct activation_record temp;
  temp.numParams=num+1;
  if(strstr(data[row], "()")!=NULL) {
    temp.numParams=0;
  }
  temp.returnAddress=row*20+20;
  stack[++topofStack]=temp;
}

int checkFunctionDef(int row, int col) {
  int i;
  for(i=0;i<col;i++) {
    if(!isalnum(data[row][i])) {
      return 0;
    }
  }
  i=0;
  while (data[row][i]!='\0') {
    i++;
  }
  i--;
  if(data[row][i]==';')
    return 0;
  else
    return 1;
}


int checkFunctionCall(int row, int col) {
  int i=0;
  while (data[row][i]!='\0') {
    i++;
  }
  i--;
  if(data[row][i]!=';')
    return 0;
  else
    return 1;
}

int findAddress(int rows) {
  int i;
  char temp[100];
  for(i=0;i<numFunctions;i++) {
    int row=funcAddress[i]/20;
    int j;
    for(j=0;data[row][j]!='(';j++) {
      temp[j]=data[row][j];
    }
    temp[j]='\0';
    if(strstr(data[rows], temp)!=NULL) {
      return funcAddress[i]+20;
    }
  }
  return 0;
}

void printFunctionName(int row) {
  int i, j, k;
  for (i = 0; data[row][i]!='('; i++) {
  }
  for(j=i-1;j>=0;j--) {
    if(!isalnum(data[row][j]))
      break;
  }
  for(k=j+1;k<i;k++)
    printf("%c", data[row][k]);
}

void scanForFunctions() {
  int i, j;
  for(i=0;i<n;i++) {
    for (j = 0; j < data[i][j]!='\0'; j++) {
      if(data[i][j]=='(') {
        if (checkFunctionDef(i, j)) {
          funcAddress[numFunctions++]=address[i];
        }
        break;
      }
    }
  }
}

void print(int num) {
  printf("\nNumber of parameters :%d\nReturn Address :%d", stack[num].numParams, stack[num].returnAddress);
}

int main(int argc, char const *argv[]) {

  int i;
  printf("\nEnter the number of statements :");
  scanf("%d", &n);
  printf("\nEnter the statements :");
  gets(data[0]);
  for(i=0;i<n;i++) {
    gets(data[i]);
  }
  address[0]=0;
  for(i=1;i<n;i++)
    address[i]=address[i-1]+20;
  scanForFunctions(); //record addresses of all function definitions

  for(i=0;i<n;i++) {
    if(strstr(data[i], "return")!=NULL) {
      endAddress=address[i];
      break;
    }
  }

  curAddress=startAddress;

  while (curAddress!=endAddress && curAddress!=0) {

    int row=curAddress/20, j;

    if(strstr(data[row], "return")!=NULL) {
      printf("\nPop Activation Record");
      struct activation_record temp=stack[topofStack];
      curAddress=temp.returnAddress;
      printf("\nFunction :");
      int tempRow=curAddress/20-1;
      printFunctionName(tempRow);
      print(topofStack);
      printf("\n");
      topofStack--;
      continue;
    }


    for (j = 0; data[row][j]!='\0'; j++) {
      if(data[row][j]=='(') {
        if (checkFunctionCall(row, j)) {
          push(row);
          printf("\nPushing Activation record");
          printf("\nFunction :");
          printFunctionName(row);
          print(topofStack);
          printf("\n");
          curAddress=findAddress(row);
        }
        else
         curAddress+=20;
        break;
      }

    }
    if(data[row][j]=='\0')
      curAddress+=20;
  }
  return 0;
}
