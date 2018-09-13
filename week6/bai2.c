#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"libfdr/jrb.h"

typedef JRB Graph;

Graph creategraph()
{
  return make_jrb();
}                               //tuongduong:make_jrb().
void addedge(Graph g,int v1,int v2)
{
  Graph tree;       //khongduoc khoitao :make_jrb(),se xoahet dulieu cu.
  JRB node;
  node=jrb_find_int(g,v1);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_int(g,v1,new_jval_v(tree));
    }
  else
    tree=(JRB)jval_v(node->val);
  jrb_insert_int(tree,v2,new_jval_i(1));
}
int getadjacentvertices(Graph g,int v,int *output)
{
  JRB node,node2;
  Graph tree;
  int total=0;
  if(g==NULL) return 0;    //can kiemtra dautien,neukhongseloi.
  //tree=make_jrb(); 
  node=jrb_find_int(g,v); 
  if(node==NULL) return 0;
  tree=(JRB)jval_v(node->val);
  jrb_traverse(node2,tree)
    { 
      output[total++]=jval_i(node2->key);
      printf("%d  --- %d\n",v,output[total-1]);//khongduocviet:total--
    }
  return total;
}
void dropgraph(Graph *g)
{
  JRB node;
  Graph graph;
  graph = (JRB)*g;
  jrb_traverse(node,graph)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(*g);
  *g=NULL;
}

int main()
{
  Graph g;
  int *output;
  g=creategraph();
  addedge(g,1,2);
  addedge(g,1,3);
  addedge(g,1,5);
  output=(int *)malloc(8*sizeof(int));   //batbuoc phaicapphat.
  getadjacentvertices(g,1,output);
  dropgraph(&g);
  free(output);
  return 0;
}
