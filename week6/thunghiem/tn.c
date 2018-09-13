#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"libfdr/jrb.h"

typedef JRB Graph;

Graph creategraph()
{
  return make_jrb();
}
void addedge(Graph g,int v1,int v2)
{
  Graph tree;
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
int getadj(Graph g,int v,int *out)
{
  JRB node,node2;
  Graph tree;
  int total=0;
  if(g==NULL) return 0;
  node=jrb_find_int(g,v);
  if(node==NULL) return 0;
  tree=(JRB)jval_v(node->val);
  jrb_traverse(node2,tree)
    {
      out[total++]=jval_i(node2->key);
      printf("%d --- %d\n",v,jval_i(node2->key));
    }
  return total;
}
void dropgraph(Graph *g)
{
  JRB node;
  Graph graph;
  graph=(JRB)*g;
  jrb_traverse(node,graph)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(*g);
  (*g)=NULL;
}
void search(Graph g,int v,int *out)
{
  JRB node,node2;
  Graph tree;
  int total=0;
  if(g==NULL) return ;
  node=jrb_find_int(g,v);
  if(node==NULL) return ;
  tree=(JRB)jval_v(node->val);
  jrb_traverse(node2,tree)
    {
      out[total++]=jval_i(node2->key);
      printf("%d ---%d\n",v,jval_i(node2->key));
    }
}

int main()
{
  Graph g;
  int *out;
  int i,j;
  int v1,v2;
  out=(int *)malloc(sizeof(int)*10);
  g=creategraph();
  printf("nhap so luong nut:");
  scanf("%d",&i);
  for(j=0;j<i;j++)
    {
      printf("enter v:");
      scanf("%d",&v1);
      printf("enter u:");
      scanf("%d",&v2);
      addedge(g,v1,v2);
    }
  printf("nhap so lan ban muon thuc hien chuc nang nay:");
  scanf("%d",&i);
  for(j=0;j<i;j++)
    {
      printf("enter button need to see:");
      scanf("%d",&v1);
      getadj(g,v1,out);
    }
  dropgraph(&g);
  free(out);
  return 0;
}
