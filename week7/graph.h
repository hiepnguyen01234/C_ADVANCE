#include<stdio.h>
#include<stdlib.h>

#include"libfdr/jrb.h"
#include"libfdr/dllist.h"

typedef JRB Graph;

Graph creategraph();
void addedge(Graph g,int v1,int v2);
int getadj(Graph g,int v,int *output);
void drophgraph(Graph *g);
