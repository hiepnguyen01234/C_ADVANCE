#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"thuvien.h"

graph create_graph()
{
  return make_jrb();
}
void add_edge(graph g, int v, int v2)
{
     if(adjacent(g, v, v2))
        return;
}
int adjacent(graph g, int v, int v2){
     if(g == NULL)
          return 0;
                                    
     JRB node = jrb_find_int(g, v);                           
     JRB tree;                                                
     if(node == NULL)                                         
          return 0;                                               
     tree = (JRB) jval_v(node->val);                      
     JRB f = jrb_find_int(tree, v2);
     if(f != NULL)
          return 1;
     return 0;

}
int get_adjacent_vertices(graph g, int vertex, int *output){
     if(g == NULL)
          return 0;
     JRB node = jrb_find_int(g, vertex);                           
     JRB tree;
     if(node == NULL)                                         
          return 0;
     int total = 0;
     tree = (JRB) jval_v(node->val);
     jrb_traverse(node, tree)
          output[total++] = jval_i(node->key);
     return total;
}
void drop_graph(graph *g){
     JRB graph = (JRB) *g;
     JRB node;
     jrb_traverse(node, graph)
          jrb_free_tree(jval_v(node->val));
     jrb_free_tree(*g);
     *g = NULL;
}
void BFS(graph g, int start, int stop, void (*visited_func)(int)){
     JRB tmp;
     int v = 0;
     jrb_traverse(tmp, g){
          v++;
     }
     
     int *visited = (int*)malloc(v * sizeof(int));
     if(visited == NULL){
          fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
          exit(1);
     }
     
     int i;
     for(i = 0; i < v; i++) visited[i] = 0;
     
     Dllist queue = new_dllist();
     


     // add start node to queue
     JRB node = jrb_find_int(g, start);
     if(node == NULL)
          goto end;
         

     dll_append(queue, new_jval_i(start));
     //
   


     while(!dll_empty(queue)){
          Dllist node = dll_first(queue);
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
         

          jrb_traverse(tmp, vertex_connect_to_u_tree){
               if(!visited[tmp->key.i])
                    dll_append(queue, new_jval_i(tmp->key.i));
          }
     }
end:
     free(visited);
     free_dllist(queue);
}

void DFS(graph g, int start, int stop, void (*visited_func)(int)){
     JRB tmp;
     int v = 0;
     jrb_traverse(tmp, g){
          v++;
     }
     
     int *visited = (int*)malloc(v * sizeof(int));
     if(visited == NULL){
          fprintf(stderr, "Allocated failed in %s:%d \n", __FILE__, __LINE__);
          exit(1);
     }
     
     int i;
     for(i = 0; i < v; i++) visited[i] = 0;
     
     Dllist stack = new_dllist();
     


     // add start node to stack
     JRB node = jrb_find_int(g, start);
     if(node == NULL)
          goto end;
         

     dll_append(stack, new_jval_i(start));
     //
   


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

void findAdjacentStations(char *stationName){
	int i;
	for (i = 0; i < data.station_num; i++)
	{
		if (strcmp(data.stations_list[i].name, stationName) == 0)
		{
			PRINT_ADJACENT_STATIONS(i+1);
			break;
		}
	}

}                                                    


map get_data_from_file(const char *file_name){
	FILE *f = fopen(file_name, "r");
     if (f == NULL) {
          fprintf(stderr, "Can't Open file %s !!\n", file_name);
          exit(1);
     }
	char temp[100];	

     //read pass [STATIONS]
     while(1){
     	fgets(temp, 100, f);
     	if (strcmp(temp, "[STATIONS]\n") == 0)
     	{
     		break;
     	}
     }

     //initialize return variable
     int MAX = 10;
     map ret;
     ret.stations_list = (station *)malloc(sizeof(station) * MAX);
     ret.station_num = 0;
     ret.graph = create_graph();

     //station name parse
     while(1){
     	fgets(temp, 100, f);
     	if (strcmp(temp, "[LINES]\n") == 0)
     	{
     		break;
     	}
     	if (strcmp(temp, "\n") == 0)
     	{
     		//blank line so continue to scan
     		continue;
     	}

     	// int i;
      //     for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
      //     if (temp[i] == '\0')
      //          continue;

     	//realloc if needed
     	if (ret.station_num == MAX -1)
     	{
     		MAX += 10;
     		ret.stations_list = (station *)realloc(ret.stations_list, sizeof(station) * MAX);
     		if (ret.stations_list == NULL) {
                    fprintf(stderr, "Reallocate failed in %s:%d !!\n", __FILE__, __LINE__);
                    exit(1);
               }
     	}

     	sscanf(temp, "S%*d=%[^\n]s\n", ret.stations_list[ret.station_num++].name);
     }

     //lines parse
     while(1){
     	fgets(temp, 100, f);
     	
     	if (strcmp(temp, "\n") == 0)
     	{
     		continue;
     	}

     	// int i;
      //     for (i = 0; temp[i] != '\0' && temp[i] != '='; i++);
      //     if (temp[i] == '\0')
      //          continue;

     	char temp2[100];
     	sscanf(temp, "M%*d=%[^\n]s\n", temp2);

     	char *p = strtok(temp2, " ");
     	int v1;
     	v1 = p[1] - '0';
     	p = strtok(NULL, " ");
     	while(p != NULL){
     		int v2;
     		v2 = p[1] - '0';
     		add_edge(ret.graph, v1, v2);
     		v1 = v2;
     		p = strtok(NULL, " ");
     	}
     	if (feof(f))
     	{
     		break;
     	}
     }
     fclose(f);
     return ret;
}
