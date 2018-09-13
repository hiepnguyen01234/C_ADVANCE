#include<stdio.h>
#include<stdlib.h>
#include"libfdr/dllist.h"
#include"libfdr/jrb.h"

typedef struct
{
  JRB edges;
  JRB vertices;
}Graph;

void visited_func(Graph g,int u);

Graph creategraph();
void addvertex(Graph g,int id,char *name);
char *getvertex(Graph g,int id);
void addedge(Graph g,int v1,int v2);
int hasedge(Graph g,int v1,int v2);
int indegree(Graph g,int v,int *output);
int outdegree(Graph g,int v,int *output);
int DAG(Graph g);
//int DAG(Graph g,int start);
void TSort(Graph g);
//void TSort(Graph g,void (*visited_func)(Graph, int));
//void TSort(Graph g, int *output,int *n);
void dropgraph(Graph *g);



