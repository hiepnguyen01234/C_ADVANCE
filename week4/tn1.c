#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "../libfdr/jrb.h"

int main()
{
  JRB tree;
  JRB j;
  Jval val[5];
  tree= make_jrb();
  val[0]=new_jval_s("thang");
  jrb_insert_int( tree,123,val[0]);
  val[0]=new_jval_s("hieu");
  jrb_insert_int( tree,456,val[1]);
  j=jrb_find_int(tree,123);
  printf("\ngia tri can tra ve :%s.\n",jval_s(j->val));
  j=jrb_find_int(tree,456);
  printf("\ngia tri can tra ve :%s.\n",jval_s(j->val));
  jrb_delete_node(tree);
  jrb_free_tree(tree);
  //jrb_iprint_tree(tree,2); 
  /*  void jrb_iprint_tree(JRB t,int level)
  {
    int i;
    if(ishead(t) && t->parent ==t)
      {
	printf("tree 0x%x is empty\n",t);
      }
    else if(ishead(t))
      {
	printf("head :0x%x. root=0x%x,< = 0x%x,> = 0x%x k=%d\n",t,isred(t)?"r":"b",isleft(t)?'l':'r',t->parent,t->blink,t->flink,t->key.i);
      }
else
  {
    jrb_iprint_tree(t->flink,level+2);
    jrb_iprint_tree(t->blink,level+2);
    for(i=0;i<level;i++)
      putchar(' ');
    printf("int node 0x%x: %c,%c:l=0w%x,r=0x%x,r=0x%x,p=0x%x,lr=(%d,%d)\n",t,isred(t)?'r':'b',isleft(t)?'l':'r',t->flink,t->blink,t->parent,getlext(t->key.i,getrext(t)->key.i);
  }
  }
  }*/
  return 0;
}
