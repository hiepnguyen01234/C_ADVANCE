#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"libfdr/dllist.h"
#include"libfdr/jrb.h"


void addvertex();
int getadj(JRB g, JRB t, char *v1) ;
void addEdges(JRB g, char *v1, char *v2) ;

