#include"graph.h"
#define max 10

void visited_func(int n)
{
  printf("%d\n",n);
}

void DFS(Graph g, int start, int stop, void (*visited_func)(int)){
     JRB tmp;
     int v = 0;
     jrb_traverse(tmp, g){
          v++;
     }
     
     int *visited = (int*)malloc(v * sizeof(int));  
     int i;
     for(i = 0; i < v; i++) visited[i] = 0;     
     Dllist stack = new_dllist();
     
     //duyetnut
     JRB node = jrb_find_int(g, start);
     if(node == NULL)
          goto end;      

     dll_append(stack, new_jval_i(start));
     while(!dll_empty(stack)){
          Dllist node = dll_last(stack);
          int u = jval_i(node->val);
          dll_delete_node(node);
          
          if(!visited[u]){
               visited_func(u);
               visited[u] = 1;
          }    
          if(u == stop) 
               goto end;     
          JRB u_node = jrb_find_int(g, u);
          if(u_node == NULL)
               continue;  
          JRB vertex_connect_to_u_tree = (JRB)(jval_v(u_node->val));
          jrb_rtraverse(tmp, vertex_connect_to_u_tree){
               if(!visited[tmp->key.i])
                    dll_append(stack, new_jval_i(tmp->key.i));
          }
     }

end:
     free(visited);
     free_dllist(stack);
}


int main()
{
  Graph g;
  int *output;
  g =creategraph();
  output=(int*)malloc(sizeof(int)*max);
  addedge(g,1,2);
  addedge(g,1,3);
  addedge(g,2,4);
  addedge(g,4,5);
  addedge(g,3,5);
  DFS(g,1,5,visited_func);
  //getadj(g,1,output);
  dropgraph(&g);
  return 0;
}
