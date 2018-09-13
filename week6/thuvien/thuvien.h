#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "libfdr/jrb.h"
#include "libfdr/dllist.h"

typedef JRB graph;
typedef struct station_s {
     char name[100];
} station;

typedef struct map_s {
     station *stations_list;
     int station_num;
     graph graph;
} map;

map get_data_from_file(const char *file_name);
void PRINT_ADJACENT_VERTIES(int v);
void findAdjacentStations(char* stationName);		


extern graph create_graph();
extern void add_edge(graph g,int v,int v2);
extern int adjacent(graph g,int v,int v2);
extern int get_adjacent_vertices(graph g, int vertex, int *output);
extern void drop_graph(graph *g);
extern void BFS(graph g, int start, int stop, void (*visited_func)(int));
extern void DFS(graph g, int start, int stop, void (*visited_func)(int));
