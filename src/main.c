#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
  int src, dst, wgt;
};

struct Graph{
  int nvrt, nedg;
  struct Edge* edges;
};

struct Subtree{
  int root,rank;
};

struct Graph* newGraph(int numvert,int numedge){
  //check on this because idk this properly mallocs the stuff
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->nvrt=numvert;
  graph->nedg=numedge;
  graph->edges=malloc(numedge*sizeof(struct Edge));
  return graph;
}

int getRoot(struct Subtree subtrees[], int n){
  //recursively go through subtrees to find the root
  if(subtrees[n].root!=n){
    subtrees[n].root = getRoot(subtrees,subtrees[n].root);
  }
  return subtrees[n].root;
}

void merge(struct Subtree subtrees[], int a, int b){
  int rootA = getRoot(subtrees,a);
  int rootB = getRoot(subtrees,b);

  if(subtrees[rootA].rank<subtrees[rootB].rank){
    subtrees[rootA].root=rootB;
  }
  else if(subtrees[rootA].rank>subtrees[rootB].rank){
    subtrees[rootB].root=rootA;
  }
  else{
    subtrees[rootA].root=rootB;
    subtrees[rootB].rank++;
  }
}

void doKruskal(struct Graph* graph){
  struct Edge result[graph->nvrt];

}

int main(int argc, char *argv[]){

  FILE *fp;
  char buffer[255];
  fp = fopen(argv[1], "r");
  fscanf(fp, "%s", buffer);
  printf("%s\n",buffer);
  fclose(fp);
}
