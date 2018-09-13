#include<stdio.h>
#include<stdlib.h>

#include"/home/hiep/c/c_advance/libfdr/jrb.h"

#define max 10
#define min 5

typedef struct 
{
  int i;
  char name[31];
  int j;
}kieukytu;
typedef struct
{
  kieukytu *haha;
  int size;
  int total;
  kieukytu *make(void *,void *);
  int *compare(void *,void *);
}symboltable;

void createsymboltable(kieukytu *make(void *,void *),int *compare(void *,void *),symboltable *creat)
{
creat.size=
  creat.total++;
}

int main()
{
  int i;
  char c[31];
  return 0;
}
