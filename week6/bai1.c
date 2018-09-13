#include<stdio.h>
#include "libfdr/jrb.h"
typedef JRB Graph;
void addEdge(Graph graph)
{
  Graph node;
  int v1, v2;
  JRB tree;
  printf("\nNhap v1: ");scanf("%d",&v1);
  printf("\nNhap v2: ");scanf("%d",&v2);
  node = jrb_find_int(graph, v1);
  if(node == NULL)
    {
      tree = make_jrb();
      jrb_insert_int(graph, v1, new_jval_v(tree));
      jrb_insert_int(tree, v2, new_jval_i(1));
    }
  else 
    {
      tree = (JRB) jval_v(node->val);
      jrb_insert_int(tree, v2, new_jval_i(1));
    }
}
void search(Graph graph, int v1)
{
  int output[100];
  Graph node = jrb_find_int(graph, v1);
  Graph tree = (JRB) jval_v(node->val);
  int total = 0;
  jrb_traverse(node, tree)
    output[total++] = jval_i(node->key);
  printf("\nCac canh ke cua %d la:",v1);
  int i;
  for( i=0; i<=total; i++)
    {
      printf("\n%d-%d",v1,output[i]);
    }
}
void print(Graph graph)
{
  Graph ptr;
  jrb_traverse(ptr, graph)
    {
      search( graph, jval_i(ptr->key) );
    }
  
}
int menu()
{
  int z;
  printf("\n__Menu__");
  printf("\n1.Nhap do thi");
  printf("\n2.In ra cac canh cua 1 dinh");
  printf("\n3.In danh sasch cac canh cua do thi");
  printf("\n4.Thoat");
  printf("\nNhap vao lua chon cua ban: ");
  scanf("%d",&z);
  while( z!=1 && z!=2 && z!=3 && z!=4)
    {
      printf("\nLua chon sai, xin moi nhap lai!\nNhap vao lua chon cua ban: ");
      scanf("%d",&z);
    }
  return z;
}
  void main()
  {
    Graph graph = make_jrb();
    int choice;
    
    while( choice != 4)
      {
		choice = menu();
		switch( choice )
		  {
		  case 1:
		    {
		      char c;
		      c='y';
		      while( c!='y' && c!='n')
			{
			  printf("\nNhap lai lua chon : ");
			  scanf("%c",&c);				
			}
		      while( c=='y')
			{
			  addEdge(graph);
			  printf("\nContinue(y/n)? : ");
			  while( getchar() != '\n');
			  scanf("%c",&c);				
			  
			}
		    }	break;
		  case 2: 
		      {
			int v;
			printf("\nNhap vao ten dinh: ");
			scanf("%d",&v);
			search(graph,v);
		      } break;
		  case 3:
		    {
		      print(graph);			
		    }
		    break;
		  }
      }
  }
  
