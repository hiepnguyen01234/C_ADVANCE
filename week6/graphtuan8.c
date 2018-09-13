#include"graphtuan8.h"


void addvertex(JRB g,char *id,char *name)
{
  /*JRB node;
  node=jrb_find_str(g,strdup(id));
  if(node==NULL)*/
    jrb_insert_str(g, strdup(name), new_jval_s(strdup(id)));
  return ;
}

int getadj(JRB g, JRB t, char *v1) {
	JRB search = jrb_find_str(t, v1);
	if(search == NULL)
		return 0;
	JRB node = jrb_find_str(g, jval_s(search -> val));
	if(node == NULL)
		return 0;
	JRB sub_node;
	int i = 0;
	JRB tree = (JRB)jval_v(node -> val);
	jrb_traverse(sub_node, tree) {
		i++;
		printf("%s\n", jval_s(sub_node -> key));
	}
	return i;

}

void addEdges(JRB g, char *v1, char *v2) {
	JRB node = jrb_find_str(g, v1);
	JRB tree = make_jrb();
	if(node == NULL) {
		jrb_insert_str(g, strdup(v1), new_jval_v(tree));
		jrb_insert_str(tree, strdup(v2), new_jval_i(0));
	} else {
		jrb_insert_str((JRB)jval_v(node -> val), strdup(v2), new_jval_i(1));
	}
}

