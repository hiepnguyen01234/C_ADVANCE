#include<stdio.h>
#include"graph.h"

int main()
{
  Graph g;
  int *output;
  int i;
  output=(int *)malloc(sizeof(int));
  g=creategraph();
  addvertex(g,1,"v1");
  addvertex(g,2,"v2");
  addvertex(g,3,"v3");
  addedge(g,1,2);
  addedge(g,1,3);
  addedge(g,5,1);
  addedge(g,9,1);
  addedge(g,2,3);
  addedge(g,3,1);

  //indegree(g,1,output);
  outdegree(g,1,output);

  if(DAG(g,1))
    printf("the graph is acycle.\n");
  else
  printf("the graph has cycles\n");

  free(output);
  dropgraph(&g);
  return 0;
}
