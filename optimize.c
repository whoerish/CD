#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>

int getNum(char s[], int index) {
  int value=0;
  for(;isdigit(s[index]);index++) {
    value*=10;
    value+=(s[index]-'0');
  }
  return value;
}

int main(int argc, char const *argv[]) {
  char exp[100][100];
  int numStatements;
  printf("\nEnter the number of statements :");
  scanf("%d", &numStatements);
  int i;
  int valid[numStatements], value[26], flag[26];

  for(i=0;i<26;i++) {
    value[i]=0;
    flag[i]=0;
  }
  for (i = 0; i < numStatements; i++) {
    valid[i]=1;
  }
  gets(exp[0]);
  for (i = 0; i < numStatements; i++) {
    int firstOp=1, secondOp=1, firstOpVal, secondOpVal, opIndex, close=1;
    gets(exp[i]);

    if(exp[i][0]=='}') {
      if(close==0)
        valid[i]=0;
      continue;
    }
    if(exp[i][0]=='i') {
      if((isalpha(exp[i][3]) && flag[exp[i][3]-'a']==1 && value[exp[i][3]-'a']==0) || exp[i][3]=='0') {
        valid[i]=0;
      while (1) {
        i=i+1;
        gets(exp[i]);
        valid[i]=0;
        if(exp[i][0]=='}') {
          break;
        }
      }
      continue;
    }
    if((isalpha(exp[i][3]) && flag[exp[i][3]-'a']==1 && value[exp[i][3]-'a']==0) || (isdigit(exp[i][3]) && exp[i][3]!='0')) {
      valid[i]=0;
      close=0;
      continue;
    }
    else {
      close=1;
      continue;
    }
   }

    if(exp[i][0]=='r') {
      valid[i]=0;
      while (i<numStatements) {
        i=i+1;
        gets(exp[i]);
        valid[i]=0;
      }
      continue;
    }


    //for first operand
    if(isdigit(exp[i][2])) {
      firstOp=0; //indicating number
      firstOpVal=getNum(exp[i], 2); //get the value
      int j=2;
      while (isdigit(exp[i][j])) {
        j++;
      }
      if(exp[i][j]!='\0')
        opIndex=j; //index of operator
      else {
        value[exp[i][0]-'a']=firstOpVal;
        flag[exp[i][0]-'a']=1;
        continue;
      }
    }
    else {
      if(flag[exp[i][2]-'a']) {
        firstOpVal=value[exp[i][2]-'a']; //set value
        firstOp=0; //indicating number
      }
      if(exp[i][3]!='\0')
        opIndex=3; //index of operator
      else {
        value[exp[i][0]-'a']=value[exp[i][2]-'a'];
        flag[exp[i][0]-'a']=flag[exp[i][2]-'a'];
        if(flag[exp[i][0]-'a']) {
          sprintf(exp[i]+2, "%d", value[exp[i][0]-'a']);
        }
        continue;
      }
    }
    //for second operand
    if(isdigit(exp[i][opIndex+1])) {
      secondOp=0; //indicating number
      secondOpVal=getNum(exp[i], opIndex+1); //get number
    }
    else {
      if(flag[exp[i][opIndex+1]-'a']) {
        secondOp=0; //indicating number
        secondOpVal=value[exp[i][opIndex+1]-'a']; //get number
      }
    }


    if(firstOp==0 && secondOp==0) {//calculate value;
      int ans;
      switch (exp[i][opIndex]) {
        case '+':ans=firstOpVal+secondOpVal;
            break;
        case '-':ans=firstOpVal-secondOpVal;
            break;
        case '*':ans=firstOpVal*secondOpVal;
            break;
        case '/':ans=firstOpVal/secondOpVal;
            break;
        case '^':ans=(int)pow(firstOpVal, secondOpVal);
            break;
      }
      sprintf(exp[i]+2, "%d", ans);
      value[exp[i][0]-'a']=ans;
      flag[exp[i][0]-'a']=1;
    }


    else if(firstOp==1 && secondOp==0) {
      switch (exp[i][opIndex]) {
        case '+':if(secondOpVal==0) {
            if(exp[i][2]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
        }
        else
          sprintf(exp[i]+opIndex+1, "%d", secondOpVal);
            break;
        case '-':if(secondOpVal==0) {
            if(exp[i][2]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
        }
        else
        sprintf(exp[i]+opIndex+1, "%d", secondOpVal);
            break;
        case '*':if(secondOpVal==1) {
            if(exp[i][2]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
        }
        else if(secondOpVal==0) {
          sprintf(exp[i]+2, "%d", 0);
          value[exp[i][0]-'a']=0;
          flag[exp[i][0]-'a']=1;
        }
        else if(secondOpVal==2) {
          exp[i][opIndex]='+';
          exp[i][opIndex+1]=exp[i][opIndex-1];
          exp[i][opIndex+2]='\0';
        }
        else
        sprintf(exp[i]+opIndex+1, "%d", secondOpVal);
            break;
        case '/':if(secondOpVal==1) {
            if(exp[i][2]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
        }
        else
        sprintf(exp[i]+opIndex+1, "%d", secondOpVal);
            break;
        case '^':if(secondOpVal==1) {
            if(exp[i][2]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
        }
           else if(secondOpVal==2) {   //a^2=a*a
            exp[i][opIndex]='*';
            exp[i][opIndex+1]=exp[i][opIndex-1];
            exp[i][opIndex+2]='\0';
        }
        else if(secondOpVal==0) {
          sprintf(exp[i]+2, "%d", 1);
          value[exp[i][0]-'a']=1;
          flag[exp[i][0]-'a']=1;
        }
        else
        sprintf(exp[i]+opIndex+1, "%d", secondOpVal);
            break;
      }

    }

    else if(firstOp==0 && secondOp==1) {
      switch (exp[i][opIndex]) {
        case '+':if(firstOpVal==0) {
            if(exp[i][opIndex+1]==exp[i][0])
              valid[i]=0;
            else{
              exp[i][opIndex]='\0';
              exp[i][2]=exp[i][opIndex+1];
            }
        }
        else {
          exp[i][2]=exp[i][opIndex+1];
          exp[i][3]=exp[i][opIndex];
          sprintf(exp[i]+4, "%d", firstOpVal);
        }
            break;
        case '-':if(firstOpVal==0) {
            if(exp[i][opIndex+1]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
              exp[i][2]=exp[i][opIndex+1];
        }
        else {
          exp[i][2]=exp[i][opIndex+1];
          exp[i][3]=exp[i][opIndex];
          sprintf(exp[i]+4, "%d", firstOpVal);
        }
            break;
        case '*':if(firstOpVal==1) {
            if(exp[i][opIndex+1]==exp[i][0])
              valid[i]=0;
            else
              exp[i][opIndex]='\0';
              exp[i][2]=exp[i][opIndex+1];
        }
        else if(firstOpVal==2) {
          exp[i][opIndex]='+';
          exp[i][opIndex-1]=exp[i][opIndex+1];
          exp[i][opIndex+2]='\0';
        }
        else if(firstOpVal==0) {
          sprintf(exp[i]+2, "%d", 0);
          value[exp[i][0]-'a']=0;
          flag[exp[i][0]-'a']=1;
        }
        else {
          exp[i][2]=exp[i][opIndex+1];
          exp[i][3]=exp[i][opIndex];
          sprintf(exp[i]+4, "%d", firstOpVal);
        }
            break;
        case '/':if(firstOpVal==0) {
          sprintf(exp[i]+2, "%d", 0);
          value[exp[i][0]-'a']=0;
          flag[exp[i][0]-'a']=1;
        }
        else {
          exp[i][2]=exp[i][opIndex+1];
          exp[i][3]=exp[i][opIndex];
          sprintf(exp[i]+4, "%d", firstOpVal);
        }
            break;
        case '^':if(firstOpVal==1) {
          sprintf(exp[i]+2, "%d", 1);
          value[exp[i][0]-'a']=1;
          flag[exp[i][0]-'a']=1;
        }
        else if(firstOpVal==0) {
          sprintf(exp[i]+2, "%d", 0);
          value[exp[i][0]-'a']=0;
          flag[exp[i][0]-'a']=1;
        }
        else {
          exp[i][2]=exp[i][opIndex+1];
          exp[i][3]=exp[i][opIndex];
          sprintf(exp[i]+4, "%d", firstOpVal);
        }
            break;
      }
    }

    else if(firstOp==1 && secondOp==1) {
      switch (exp[i][opIndex]) {
        case '-': if(exp[i][opIndex-1]==exp[i][opIndex+1]){
          sprintf(exp[i]+2, "%d", 0);
          value[exp[i][0]-'a']=0;
          flag[exp[i][0]-'a']=1;
        }
          break;

        case '/':if(exp[i][opIndex-1]==exp[i][opIndex+1]){
          sprintf(exp[i]+2, "%d", 1);
          value[exp[i][0]-'a']=1;
          flag[exp[i][0]-'a']=1;
        }
          break;

      }
    }
  }

  for(i=0;i<numStatements;i++) {
    if(valid[i])
      puts(exp[i]);
  }
  return 0;
}
