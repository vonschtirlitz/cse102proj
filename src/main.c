#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Edge{
  int src, dst, wgt, id;
};

struct Graph{
  int nvrt, nedg;
  struct Edge* edges;
};

struct ResultEdge{
  int nresult;
  struct Edge* resultEdges;
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
  //struct ResultEdge* result = malloc(sizeof(struct ResultEdge));
  struct Edge result[graph->nvrt];
  struct Edge temp;
  int tempEdge;
  int resultIter;


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

  //debug print graph
  for(int i=0;i<graph->nedg;i++){
    printf("%i: %i, %i, %i\n",
    graph->edges[i].id,
    graph->edges[i].src,
    graph->edges[i].dst,
    graph->edges[i].wgt);
  }

  //initialize subtrees
  struct Subtree *subtrees =
  (struct Subtree*)malloc(graph->nvrt*sizeof(struct Subtree));
  for(int i=0;i<graph->nvrt;i++){
    subtrees[i].root = i;
    subtrees[i].rank = 0;
  }

  while (resultIter < graph->nvrt-1 && tempEdge < graph->nedg){
    struct Edge next_edge = graph->edges[tempEdge++];

    int x = getRoot(subtrees, next_edge.src);
    int y = getRoot(subtrees, next_edge.dst);
    if (x != y)
    {
      result[resultIter++] = next_edge;
      merge(subtrees, x, y);
    }
    // Else discard the next_edge
  }
  printf("----\n");
  int totalweight;
  for(int i=0;i<resultIter;i++){
    printf("%i: %i, %i, %i\n",
    result[i].id,
    result[i].src,
    result[i].dst,
    result[i].wgt);

    /*fprintf(output, "    %i: (%i, %i) %f\n",result[i].id,
    result[i].src,
    result[i].dst,
    result[i].wgt);
    totalweight+=result[i].wgt;*/
  }
  /*fprintf(output,"Total Weight = %f\n",totalweight);
  printf("Total Weight = %f\n",totalweight);*/



  //result->nresult=resultIter;
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



  //debug
  //printf("%i ",(int)sizeof(graph->edges));
  //printf("%i\n",(int)sizeof(struct Edge));

  while(fscanf(fp, "%s", buffer)!=EOF){

    graph->edges[edgeindex].src=atoi(buffer);

    fscanf(fp, "%s", buffer);
    graph->edges[edgeindex].dst=atoi(buffer);

    fscanf(fp, "%s", buffer);
    graph->edges[edgeindex].wgt=atoi(buffer);

    graph->edges[edgeindex].id=edgeindex+1;
    edgeindex++;
  }

  //debug input print
  for(int i=0;i<graph->nedg;i++){
    printf("%i: %i, %i, %i\n",graph->edges[i].id,
    graph->edges[i].src,
    graph->edges[i].dst,
    graph->edges[i].wgt);
  }

  printf("----\n");

  doKruskal(graph);



  printf("done\n");

  fclose(fp);
  fclose(fp2);
}
