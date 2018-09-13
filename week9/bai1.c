#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "libfdr/dllist.h"
#include "libfdr/jrb.h"
#define INFINITIVE_VALUE 10000000

typedef struct {
  JRB vertices;
  JRB edges;
} graph;

graph createGraph() {
  graph g;
  g.vertices = make_jrb();
  g.edges = make_jrb();
  return g;
}

void addVertices(graph g, int v, char *name) {
  JRB node;
  node = jrb_find_int(g.vertices, v);
  if (node == NULL) {
    jrb_insert_int(g.vertices, v, new_jval_s(strdup(name)));
  } else {
    strcpy(jval_s(node->val), name);
  }
}

void addEdges(graph g, int v1, int v2, double weight) {
  if (jrb_find_int(g.vertices, v1) == NULL ||
      jrb_find_int(g.vertices, v2) == NULL)
    return;
  JRB node = jrb_find_int(g.edges, v1);
  if (node == NULL) {
    JRB tree = make_jrb();
    jrb_insert_int(g.edges, v1, new_jval_v(tree));
    jrb_insert_int(tree, v2, new_jval_d(weight));
  } else {
    jrb_insert_int((JRB)jval_v(node->val), v2, new_jval_d(weight));
  }
}

double getEdgeValue(graph g, int v1, int v2) {
  if (jrb_find_int(g.vertices, v1) == NULL || jrb_find_int(g.vertices, v2) == NULL) {
    return INFINITIVE_VALUE;
  }
  JRB node, sub_node;
  node = jrb_find_int(g.edges, v1);
  if(node == NULL) {
    return INFINITIVE_VALUE;
  }
  sub_node = jrb_find_int((JRB)jval_v(node -> val), v2);
  if(sub_node == NULL) {
    return INFINITIVE_VALUE;
  }
  return jval_d(sub_node -> val);
}

int indegree(graph g, int v, int *output) {
  JRB node, sub_node;
  int total = 0;
  node = jrb_find_int(g.vertices, v);
  if (node == NULL)
    return total;
  jrb_traverse(node, g.edges) {
    sub_node = jrb_find_int((JRB)jval_v(node->val), v);
    if (sub_node != NULL)
      output[total++] = jval_i(node->key);
  }
  return total;
}

int outdegree(graph g, int v, int *output) {
  JRB node, sub_node;
  int total = 0;
  if (jrb_find_int(g.vertices, v) == NULL)
    return total;
  if ((node = jrb_find_int(g.edges, v)) == NULL)
    return total;
  JRB tree = (JRB)jval_v(node->val);
  jrb_traverse(sub_node, tree) { output[total++] = jval_i(sub_node->key); }
  return total;
}

double shortestPath(graph g, int s, int t, int *path, int *length) {
  if(g.edges == NULL || g.vertices == NULL)
    return INFINITIVE_VALUE;
  if(path == NULL || length == NULL)
    return INFINITIVE_VALUE;
  int v = 0;
  JRB node;
  jrb_traverse(node, g.vertices) {
    v++;
  }
  double *d = malloc(sizeof(double) * v);
  double *p = malloc(sizeof(double) * v);
  int i;
  Dllist queue = new_dllist();
  jrb_traverse(node, g.vertices) {
    int u = jval_i(node -> key);
    if(u != s) {
      d[u] = INFINITIVE_VALUE;
      p[u] = -1;
    }
    dll_append(queue, new_jval_i(u));
  }
  d[s] = 0;
  while(!dll_empty(queue)) {
    int u;
    {
    Dllist tmp, min_node = dll_first(queue);
    int min = jval_i(min_node -> val);
    dll_traverse(tmp, queue) {
      int tmp_node_i = jval_i(tmp -> val);
      if(d[min] > d[tmp_node_i]) {
        min = tmp_node_i;
        min_node = tmp;
      }
    }
    u = min;
    dll_delete_node(min_node);
    }
    int *output = malloc(sizeof(int) * v);
    int n = outdegree(g, u, output);
    
    if(n == 0)
      continue;
    for( i = 0; i < n; i++) {
      int k = output[i];
      double alt = d[u] + getEdgeValue(g, u, k);
      if(alt < d[k]) {
        d[k] = alt;
        p[k] = u;
      }
    }
    free(output);
  }
  for( i = 0; i < v; i++) {
    length[i] = d[i];
  }
 
  if (p[t] != -1) {
    int j = 1;
    path[0] = t;
    while (1) {
      path[j] = p[path[j - 1]];
      if (path[j] == s || path[j] == -1)
        break;
      j++;
    }
    for( i = ++j; i < v; ++i) {
      path[j] = -1;
    }
  }
  double ret = d[t];
  free_dllist(queue);
  free(d);
  free(p);
  return ret;
}

int main() {
  int *path, *length;
  int v = 0;
  JRB node;
  
  graph g = createGraph();
  addVertices(g, 0, "V0");
  addVertices(g, 1, "V1");
  addVertices(g, 2, "V2");
  addVertices(g, 3, "V3");
  addVertices(g, 4, "V4");
  addVertices(g, 5, "V5");
  addEdges(g, 0, 1, 3);
  addEdges(g, 1, 2, 1);
  addEdges(g, 0, 2, 5);
  addEdges(g, 2, 3, 2);
  addEdges(g, 2, 4, 4);
  addEdges(g, 3, 1, 5);
  addEdges(g, 3, 5, 5);
  addEdges(g, 4, 5, 1 );
  jrb_traverse(node, g.vertices) { v++; }
  path = (int *)malloc(sizeof(int) * v);
  length = (int *)malloc(sizeof(int) * v);
  int check = shortestPath(g, 0, 5, path, length);
  printf("%d\n", check); 
  printf("Duong di\n");
  int i = 0;
  while(path[i] != -1 && i < v) {
    printf("Buoc %d : %d\n", i + 1, path[i]);
    i++;
  }
  
  return 1;
}
