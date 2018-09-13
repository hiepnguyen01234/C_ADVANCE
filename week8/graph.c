#include"graph.h"


void visited_func(Graph g,int u)
{
  JRB node;
  node=jrb_find_int(g.edges,u);
  if(node==NULL)
    return;
  JRB tree;
  tree = (JRB) jval_v(node->val);
  jrb_traverse(node,tree)
    printf("%d\n",jval_i(node->key));
}

Graph creategraph()
{
  Graph g;
  g.vertices=make_jrb();
  g.edges=make_jrb();
  return g;
}
void addvertex(Graph g,int id,char *name)
{
  JRB node;
  if(g.edges==NULL || g.vertices==NULL)
    return ;
  node=jrb_find_int(g.vertices,id);
  if(node ==NULL)
    jrb_insert_int(g.vertices,id,new_jval_s(name));
}
char *getvertex(Graph g,int id)
{
  JRB node;
  if(g.edges==NULL || g.vertices==NULL)
    return NULL;
  node=jrb_find_int(g.vertices,id);
  if(node!= NULL)
    return jval_s(node->val);
  return NULL;
}
int hasedge(Graph g,int v1,int v2)
{
  JRB node;
  JRB tree;
  JRB find;
  if(g.edges==NULL || g.vertices==NULL)
    return 0;

  node=jrb_find_int(g.edges,v1);
  if(node==NULL)
    return 0;
  tree=(JRB) jval_v(node->val);
  find=jrb_find_int(tree,v2);
  if(find==NULL)
    return 0;
  return 1;
}
void addedge(Graph g,int v1,int v2)
{
  JRB node;
  JRB tree;
  if (hasedge(g,v1,v2))
    return;

  node=jrb_find_int(g.edges,v1);
  if(node==NULL)
    {
      tree=make_jrb();
      jrb_insert_int(g.edges,v1,new_jval_v(tree));
    }
  else
    tree=(JRB) jval_v(node->val);
  jrb_insert_int(tree,v2,new_jval_i(1));
}
void dropgraph(Graph *g)
{
  JRB node;
  jrb_traverse(node,g->edges)
    jrb_free_tree(jval_v(node->val));
  jrb_free_tree(g->vertices);
  jrb_free_tree(g->edges);
}
int outdegree(Graph g, int vertex, int *output) {
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  JRB node = jrb_find_int(g.edges, vertex);
  if (node == NULL)
    return 0;
  int i,total = 0;
  JRB tree;
  tree = (JRB) jval_v(node->val);
  jrb_traverse(node, tree)
   {
     i=total;
     output[total++] = jval_i(node->key);
     printf("%d\n",output[i]);
   }
  return total;
}
int indegree(Graph g, int vertex, int *output) {

  if (g.edges == NULL || g.vertices == NULL)
    return 0;


  JRB node = jrb_find_int(g.vertices, vertex);
  if (node == NULL)
    return 0;

  int i,total = 0;

  jrb_traverse(node, g.vertices) {
    if (hasedge(g, jval_i(node->key), vertex)) 
    {
      i=total;
      output[total++] = jval_i(node->key);
      printf("%d\n",output[i]);
    }
  }

  return total;
}





/*int get_graph_max_id(Graph g) {
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  int max_id = 0;
  JRB tmp;
  jrb_traverse(tmp, g.vertices) {
    int key = jval_i(tmp->key);
    if (key > max_id)
      max_id = key;
  }
  return max_id;
}

int get_graph_min_id(Graph g) {
  if (g.edges == NULL || g.vertices == NULL)
    return 0;
  int min_id = 10000000;
  JRB tmp;
  jrb_traverse(tmp, g.vertices) {
    int key = jval_i(tmp->key);
    if (key < min_id)
      min_id = key;
  }
  return min_id;
}

int DAG(Graph g, int start) {
  if (g.edges == NULL || g.vertices == NULL)
    return 0;

  int max_id = get_graph_max_id(g);

  int *visited = (int*)malloc((max_id + 1) * sizeof(int));
  if (visited == NULL) {
    fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
    exit(1);
  }

  JRB node;
  jrb_traverse(node, g.vertices) {
    visited[jval_i(node->key)] = 0;
  }

  Dllist stack = new_dllist();



  // add start node to stack
  node = jrb_find_int(g.vertices, start);
  if (node == NULL)
    goto end;


  dll_append(stack, new_jval_i(start));
  //

  int flag = 0;

  while (!dll_empty(stack)) {
    Dllist node = dll_last(stack);
    int u = jval_i(node->val);
    dll_delete_node(node);

    if (!visited[u]) {
      visited[u] = 1;
      if (!flag && (u == start))
        visited[u] = 0;
    }

    if ((u == start) && (visited[start] == 1)) {
      free(visited);
      free_dllist(stack);
      return 1;
    }

    flag++;

    JRB u_node = jrb_find_int(g.vertices, u);
    if (u_node == NULL)
      continue;

    int *out_degree_u_list = malloc((max_id + 1) * sizeof(int));
    int out_degree_u;
    if(out_degree_u_list == NULL){
      fprintf(stderr, "%s %s:%d\n", "malloc failed in", __FILE__, __LINE__);
      exit(1);
    }    

    if ((out_degree_u = outdegree(g, u, out_degree_u_list)) == 0)
      continue;

    int i;
    for(i = 0; i < out_degree_u; i++){
      int _v = out_degree_u_list[i];
      if (!visited[_v])
        dll_append(stack, new_jval_i(_v));
    }

    free(out_degree_u_list);
  }

end:
  free(visited);
  free_dllist(stack);
  return 0;
}*/
int DAG(Graph g) {
  int v = 0;
  int *output;
  int dinh,i,j;
  JRB node;
  jrb_traverse(node, g.edges) { v++; }
  int *visited;
  visited = (int *)malloc(sizeof(int) * v);
  output = (int *)malloc(sizeof(int) * v);
  for ( i = 0; i < v; i++) {
    visited[i] = 0;
  }
  jrb_traverse(node, g.edges) {
    for (i = 0; i < v; i++) {
      visited[i] = 0;
    }
    Dllist queue = new_dllist();
    dll_append(queue, node->key);
    while (!dll_empty(queue)) {
      Dllist sub_node = dll_first(queue);
      int u = jval_i(sub_node->val);
      dll_delete_node(sub_node);
      if (!visited[u]) {
        visited[u] = 1;
      }

      int n = getAdjacentVertices(g.edges, u, output);
      for ( i = 0; i < n; i++) {

        if (visited[output[i]] == 0)
          dll_append(queue, new_jval_i(output[i]));
        if (output[i] == jval_i(node->key)) {
          printf("Ta co chu trinh:  ");
          for (j = 0; j < v; j++)
            if (visited[j] == 1)
              printf("%d ", j);
          printf("\n");
          return 1;
        }
      }
    }
    free_dllist(queue);
  }
  return 0;
}



/*void TSort(Graph g,void (*visited_func)(Graph, int)) {
  if (g.edges == NULL || g.vertices == NULL)
    return;

  Dllist queue = new_dllist();
  JRB tmp;

  JRB node = jrb_find_int(g.vertices, get_graph_min_id(g));
  if (node == NULL)
    goto end;

  int max_id = get_graph_max_id(g);
  int *in_degree_node = malloc(sizeof(int) * (max_id + 1));
  if (in_degree_node == NULL) {
    fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
    exit(1);
  }

  int *in_degree_arr = malloc(sizeof(int) * (max_id + 1));
  if (in_degree_arr == NULL) {
    fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
    exit(1);
  }



  jrb_traverse(tmp, g.vertices) {
    int v = jval_i(tmp->key);
    if ((in_degree_arr[v] = indegree(g, v, in_degree_node)) == 0) {
      dll_append(queue, new_jval_i(v));
    }
  }

  free(in_degree_node);
  while (!dll_empty(queue)) {
    Dllist node = dll_first(queue);
    int u = jval_i(node->val);
    dll_delete_node(node);

    visited_func(g, u);

    int *out_degree_node_u = malloc(sizeof(int) * (max_id + 1));
    if (out_degree_node_u == NULL) {
      fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
      exit(1);
    }

    int out_degree_u;
    if ((out_degree_u = outdegree(g, u, out_degree_node_u)) != 0) {
      int w, i;
      int *in_degree_node_w = malloc(sizeof(int) * (max_id + 1));
      if (in_degree_node_w == NULL) {
        fprintf(stderr, "%s in %s:%d !!\n", "malloc failed", __FILE__, __LINE__);
        exit(1);
      }
      for (i = 0; i < out_degree_u; ++i)
      {
        w = out_degree_node_u[i];

        in_degree_arr[w] -= 1;

        if (in_degree_arr[w] == 0) {
          dll_append(queue, new_jval_i(w));
        }
      }
      free(in_degree_node_w);
    }
    free(out_degree_node_u);
  }

end:
  free(in_degree_arr);
  free_dllist(queue);
}*/

int getAdjacentVertices(JRB g, int v, int *output) {
  JRB node, sub_node;
  node = jrb_find_int(g, v);
  if (node == NULL) {
    return 0;
  } else {
    int i = 0;
    JRB tree = (JRB)jval_v(node->val);
    jrb_traverse(sub_node, tree) { output[i++] = jval_i(sub_node->key); }
    return i;
  }
}
void TSort(Graph g) {
  JRB node;
  printf("Sap xep Topo:\n");
  int v = 0;
  int u,i;
  int *output;
  jrb_traverse(node, g.edges) { v++; }
  int *indr;
  indr = (int *)malloc(sizeof(int) * v);
  output = (int *)malloc(sizeof(int) * v);
  jrb_traverse(node, g.vertices) {
    indr[jval_i(node->key)] = indegree(g, jval_i(node->key), output);
  }
  Dllist queue = new_dllist();
  jrb_traverse(node, g.vertices) {
    if (indr[jval_i(node->key)] == 0) {
      u = jval_i(node->key);
    }
  }
  if (indr[u] == 0) {
    dll_append(queue, new_jval_i(u));
  }
  while (!dll_empty(queue)) {
    Dllist sub_node = dll_first(queue);
    int n = jval_i(sub_node->val);
    printf("%d\n", n);
    dll_delete_node(sub_node);
    for (i = 0; i < getAdjacentVertices(g.edges, n, output); i++) {
      indr[output[i]] = indr[output[i]] - 1;

      if (indr[output[i]] == 0)
        dll_append(queue, new_jval_i(output[i]));
    }
  }
}

