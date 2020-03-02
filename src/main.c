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
  //struct Edge sorted[graph->nvrt];
  struct Edge result[graph->nvrt];

  //sort
  int i,j;
	struct Edge temp;
	for(i=1;i<graph->nedg;i++){
		for(j=0;j<graph->nedg-1;j++){
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

  struct Subtree *subtrees =
  (struct Subtree*)malloc(graph->numvert*sizeof(struct Subtree));




}

int main(int argc, char *argv[]){

  FILE *fp;
  char buffer[255];
  fp = fopen(argv[1], "r");

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
    printf("%i: %i, %i, %i\n",graph->edges[i].id,graph->edges[i].src,graph->edges[i].dst,graph->edges[i].wgt);
  }

  printf("----\n");

  doKruskal(graph);

  fclose(fp);
}
