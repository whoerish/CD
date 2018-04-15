#include <stdio.h>
#include <string.h>
#include <math.h>
#include <ctype.h>



struct block {
  /* data */
  char statements[10][10];
  int statementNum[10];
  int numStatements;
  int vars[26];
  int kill, gen;
  int out, in, cout, cin;
};

struct flow {
  /* data */
  int numBlocks;
  int totalStatements;
  struct block b[10];
  int adj[10][10];
};
struct flow f;

void binPrint(int n) {
  int i;
  for(i=f.totalStatements-1;i>=0;i--) {
    if(n&(1<<i)) {
      printf("1");
    }
    else
      printf("0");
  }
}

void dfs(int cur, int visited[], int source) {
  visited[cur]=1;
  int i, j;

  if(source!=cur) {
    for(i=0;i<26;i++) {
      if(f.b[cur].vars[i]==f.b[source].vars[i] && f.b[cur].vars[i]==1) {
        for(j=0;j<f.b[cur].numStatements;j++) {
          if((f.b[cur].statements[j][0]-'a')==i) {
            int l=f.b[cur].statementNum[j];
            int r=l;
            int num = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
            f.b[source].kill^=num;
          }
        }
      }
    }
  }
  for(i=0;i<f.numBlocks;i++) {
    if(f.adj[cur][i] && !visited[i]) {
      dfs(i, visited, source);
    }
  }
}


int main(int argc, char const *argv[]) {
  int i, j;

  //initialize
  for(i=0;i<10;i++) {
    for(j=0;j<10;j++) { //adjacency list
      f.adj[i][j]=0;
    }
    //kill, gen, in, out
    f.b[i].gen=0;
    f.b[i].kill=0;
    f.b[i].in=0;
    f.b[i].out=0;
    f.b[i].cout=0;
    f.b[i].cin=0;

    //variables array
    for(j=0;j<26;j++) {
      f.b[i].vars[j]=0;
    }

    //stetement number
    for(j=0;j<10;j++) {
      f.b[i].statementNum[j]=0;
    }

  }

  int numBlocks;
  printf("\nEnter the number of blocks :");
  scanf("%d", &numBlocks);
  f.numBlocks=numBlocks;
  int totalStatements=0;
  for(i=0;i<numBlocks;i++) {
    printf("\nBlock %d", i);
    printf("\nEnter the number of statements :");
    scanf("%d", &f.b[i].numStatements);
    printf("\nEnter the statements :");


    char s[10];//extra read to synchronize
    gets(s);


    for(j=0;j<f.b[i].numStatements;j++) {
      gets(f.b[i].statements[j]);
      totalStatements++;
      f.b[i].statementNum[j]=totalStatements;
      f.b[i].vars[f.b[i].statements[j][0]-'a']=1;
    }
  }

  int numConnections;
  printf("\nEnter the number of connections :");
  scanf("%d", &numConnections);
  printf("\nEnter the connection x->y :");
  for(i=0;i<numConnections;i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    f.adj[x][y]=1;
  }

  for(i=0;i<numBlocks;i++) {
    for(j=0;j<f.b[i].numStatements;j++) {
      f.b[i].statementNum[j]=totalStatements-f.b[i].statementNum[j]+1;
    }
  }

  f.totalStatements=totalStatements;
  for(i=0;i<numBlocks;i++) {
    int r=totalStatements;
    totalStatements-=f.b[i].numStatements;
    int l=totalStatements+1;
    int num = ((1 << r) - 1) ^ ((1 << (l - 1)) - 1);
    f.b[i].gen^=num;
  }

  for(i=0;i<numBlocks;i++) {
    int visited[numBlocks];
    for(j=0;j<numBlocks;j++) {
      visited[j]=0;
    }
    dfs(i, visited, i);
  }

  printf("BLOCK\tGEN\tKILL\n");
  for(i=0;i<numBlocks;i++) {
    printf("%d\t",i);
    binPrint(f.b[i].gen);
    printf("\t");
    binPrint(f.b[i].kill);
    printf("\n");
  }
  printf("\n");

  for(i=0;i<numBlocks;i++) {
    f.b[i].out=f.b[i].gen;
  }
  int end=1;
  int pass=1;
  while (end) {
    printf("PASS %d\n", pass);
    printf("IN\tOUT\n");
    for(i=0;i<numBlocks;i++) {
      binPrint(f.b[i].in);
      printf("\t");
      binPrint(f.b[i].out);
      printf("\n");
    }
    printf("\n");
    pass++;

    for(i=0;i<numBlocks;i++) {
      for(j=0;j<numBlocks;j++) {
        if(f.adj[j][i]==1) {
          if(i<j)
            f.b[i].cin=f.b[i].cin|f.b[j].out;
          else
            f.b[i].cin=f.b[i].cin|f.b[j].cout;
        }
      }
      f.b[i].cout=(f.b[i].cin & (~f.b[i].kill)) | f.b[i].gen;
    }
    for(i=0;i<numBlocks;i++) {
      if(f.b[i].cout!=f.b[i].out) {
        break;
      }
    }
    if(i==numBlocks) {
      end=0;
    }
    else {
      for(i=0;i<numBlocks;i++) {
        f.b[i].out=f.b[i].cout;
        f.b[i].in=f.b[i].cin;
        f.b[i].cin=0;
        f.b[i].cout=0;
      }
    }
  }
  printf("PASS %d\n", pass);
  printf("IN\tOUT\n");
  for(i=0;i<numBlocks;i++) {
    binPrint(f.b[i].cin);
    printf("\t");
    binPrint(f.b[i].out);
    printf("\n");
  }

  return 0;
}
