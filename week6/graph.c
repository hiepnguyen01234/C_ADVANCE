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
  Graph tree;
  //g=make_jrb();
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
int getadj(Graph g,int v,int *output)
{
  JRB node;
  Graph tree;
  int total=0;
  //tree=make_jrb();   ?co can thiet khong.
  node=jrb_find_int(g,v);
  tree=(JRB)jval_v(node->val);

  if(g==NULL) return 0;
  if(node==NULL) return 0;
  
  jrb_traverse(node,tree)  //duyetnodetrongtree khongphainodekia
    {
      output[total++]=jval_i(node->key);
      printf("%d  --- %d\n",v,output[total-1]);
    }
  return total;
}
void dropgraph(Graph *g)
{
  JRB node;
  JRB graph;
  graph = (JRB)*g;
  jrb_traverse(node,graph)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(*g);
  *g=NULL;
}

/*int main()
{
  Graph g;
  int *output;
  g=creategraph();
  addedge(g,1,2);
  addedge(g,1,3);
  output=(int *)malloc(sizeof(int));
  getadj(g,1,output);
  dropgraph(&g);
  free(output);
  return 0;
}*/
