#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct node {
  int value, flag, time, numParents, numChildren, visit;
  struct node *child[5];
  struct node *parents[5];
};

typedef struct node* Node;

struct node * makeNode(int value, int flag, int time) {
  Node n=(struct node *)malloc(sizeof(struct node));
  n->value=value;
  n->flag=flag;
  n->time=time;
  n->numChildren=0;
  n->numParents=0;
  n->visit=0;
  return n;
}

void addChild(Node parent, Node child) {
  parent->child[parent->numChildren++]=child;
  child->parents[child->numParents++]=parent;
}

struct node * find(Node op1, Node op2, int value) {
  int i, j;
  for(i=0;i<op1->numParents;i++) {
    for(j=0;j<op2->numParents;j++) {
      if (op1->parents[i]==op2->parents[j] && op1->parents[i]->value==value) {
        return op1->parents[i];
      }
    }
  }
  return NULL;
}

void deleteChild(Node parent, Node child) {
  int i;
  for(i=0;i<parent->numChildren;i++) {
    if(parent->child[i]==child)
    break;
  }
  for(;i<parent->numChildren-1;i++) {
    parent->child[i]=parent->child[i+1];
  }
  parent->numChildren--;

  for(i=0;i<child->numParents;i++) {
    if(child->parents[i]==parent)
    break;
  }
  for(;i<child->numParents-1;i++) {
    child->parents[i]=child->parents[i+1];
  }
  child->numParents--;
}

int isParent(Node child, Node parent) {
  int i;
  for (i = 0; i < child->numParents; i++) {
    if(child->parents[i]==parent)
      return 1;
  }
  return 0;
}

void print(Node root) {
  int i;
  for (i = 0; i < root->numChildren; i++) {
    print(root->child[i]);
    printf("%p with character %c has %c present at %p as child\n", root, root->value, root->child[i]->value, root->child[i]);
  }
}

int main(int argc, char const *argv[]) {
  int numStatements;
  printf("\nEnter the number of statements :");
  scanf("%d", &numStatements);
  printf("Enter the statements one by one \n");
  int statement;
  char c;
  struct node *nodes[26];
  int i;
  for (i = 0; i < 26; i++) {
    nodes[i]=NULL;
  }
  Node root=makeNode(-1, 2, 0);c=getchar();
  for(statement=0;statement<numStatements;statement++) {
    int state=0;

    Node rhs, op1, op2, operator;
    while(1) {
      c=getchar();
      printf("%c", c);
      if(state==0) {
        if(nodes[c-'a']==NULL) {
          rhs=makeNode(c, 1, 1);
          addChild(root, rhs);
        }
        else {
          rhs=makeNode(c, 1, nodes[c-'a']->time+1);
          addChild(root, rhs);
        }
        state=1;
        c=getchar();
      }

      else if(state==1) {
          if(nodes[c-'a']==NULL) {
            op1=makeNode(c, 1, 1);
            nodes[c-'a']=op1;
          }
          else {
            op1=nodes[c-'a'];
          }
          c=getchar();
          operator=makeNode(c, 1, -1);
          state=2;
        }

      else if(state==2){
          if(nodes[c-'a']==NULL) {
            op2=makeNode(c, 1, 1);
            nodes[c-'a']=op2;
          }
          else {
            op2=nodes[c-'a'];
          }
          state=3;
        }
      else if(state==3) {
        Node n=find(op1, op2, operator->value);
        if(n!=NULL)
          operator=n;
        nodes[rhs->value-'a']=rhs;
        addChild(operator, op1);
        addChild(operator, op2);
        if(isParent(op1, root))
          deleteChild(root, op1);
        if(isParent(op2, root))
          deleteChild(root, op2);
        addChild(rhs, operator);
        break;
      }
    }
  }
  print(root);
  return 0;
}
