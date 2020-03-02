#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
  int src, dst, id;
  float wgt;
};

struct Graph{
  int nvrt, nedg;
  struct Edge* edges;
};

struct ResultEdge{
  int nresult;
  struct Edge* edges;
};

struct Subtree{
  int root,rank;
};

struct Graph* newGraph(int numvert,int numedge){
  struct Graph* graph = malloc(sizeof(struct Graph));
  graph->nvrt=numvert;
  graph->nedg=numedge;
  graph->edges=malloc(numedge*sizeof(struct Edge));
  return graph;
}

struct ResultEdge* newResultEdge(int numentry){
  struct ResultEdge* result = malloc(sizeof(struct ResultEdge));
  result->nresult=numentry;
  result->edges=malloc(numentry*sizeof(struct Edge));
  return result;
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

struct ResultEdge* doKruskal(struct Graph* graph){
  struct Edge result[graph->nvrt];
  struct Edge temp;
  int edgeN=0;
  int resultN=0;

  //sort
  for(int i=1;i<graph->nedg;i++){
    for(int j=0;j<graph->nedg-1;j++){
      if(graph->edges[j].wgt>graph->edges[j+1].wgt)
      {
        temp=graph->edges[j];
        graph->edges[j]=graph->edges[j+1];
        graph->edges[j+1]=temp;
      }
    }
  }
/*
  //debug print graph
  for(int i=0;i<graph->nedg;i++){
    printf("%i: %i, %i, %i\n",
    graph->edges[i].id,
    graph->edges[i].src,
    graph->edges[i].dst,
    graph->edges[i].wgt);
  }*/

  //initialize subtrees
  struct Subtree *subtrees =
  (struct Subtree*)malloc(graph->nvrt*sizeof(struct Subtree));
  for(int i=0;i<graph->nvrt;i++){
    subtrees[i].root = i;
    subtrees[i].rank = 0;
  }

  while (resultN<graph->nvrt-1 && edgeN<graph->nedg){
    temp=graph->edges[edgeN++];
    int a=getRoot(subtrees, temp.src);
    int b=getRoot(subtrees, temp.dst);
    if (a!=b)
    {
      result[resultN++]=temp;
      merge(subtrees,a,b);
    }
  }
  struct ResultEdge* finaledge = newResultEdge(resultN);
  for(int i=0;i<resultN;i++){
    finaledge->edges[i].id=result[i].id;
    finaledge->edges[i].src=result[i].src;
    finaledge->edges[i].dst=result[i].dst;
    finaledge->edges[i].wgt=result[i].wgt;
  }
  return finaledge;


  //result->nresult=resultN;
  //result->resultEdges=resultEdge;
  //return result;


}

int main(int argc, char *argv[]){

  FILE *fp;
  FILE *fp2;

  char buffer[255];
  fp = fopen(argv[1], "r");
  fp2 = fopen(argv[2], "w+");


  int numvert;
  int numedge;
  int edgeindex = 0;

  fscanf(fp, "%s", buffer);
  numvert=atoi(buffer);
  //printf("%s,%i\n",buffer,numvert);

  fscanf(fp, "%s", buffer);
  numedge=atoi(buffer);
  //printf("%s,%i\n",buffer,numedge);

  struct Graph* graph = newGraph(numvert,numedge);

  while(fscanf(fp, "%s", buffer)!=EOF){

    graph->edges[edgeindex].src=atoi(buffer);

    fscanf(fp, "%s", buffer);
    graph->edges[edgeindex].dst=atoi(buffer);

    fscanf(fp, "%s", buffer);
    graph->edges[edgeindex].wgt=atof(buffer);

    graph->edges[edgeindex].id=edgeindex+1;
    edgeindex++;
  }

  //debug input print
  /*for(int i=0;i<graph->nedg;i++){
    printf("%i: %i, %i, %i\n",graph->edges[i].id,
    graph->edges[i].src,
    graph->edges[i].dst,
    graph->edges[i].wgt);
  }
  printf("----\n");
  */

  struct ResultEdge* result = doKruskal(graph);
  float totalweight=0.0;
  for(int i=0;i<result->nresult;i++){
    fprintf(stdout, "    %i: (%i, %i) %.1f\n",result->edges[i].id,
    result->edges[i].src,
    result->edges[i].dst,
    result->edges[i].wgt);

    fprintf(fp2, "    %i: (%i, %i) %.1f\n",result->edges[i].id,
    result->edges[i].src,
    result->edges[i].dst,
    result->edges[i].wgt);
    totalweight+=result->edges[i].wgt;
  }
  fprintf(stdout, "Total Weight = %.2f\n",totalweight);
  fprintf(fp2, "Total Weight = %.2f\n",totalweight);

  printf("done\n");

  fclose(fp);
  fclose(fp2);

}
