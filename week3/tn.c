#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>

#define bigsize 10
#define minisize 3

typedef struct 
{
  void *value;
  void *key;
}entry;
typedef struct
{
  entry *entries;
  int total;
  int size;
  entry (*makenode)(void *,void *);
  int (*compare)(void *,void *);               
}symboltable;

symboltable createsymboltable(entry (*makenode)(void *,void *),int (*compare)(void *,void *))
{
  symboltable res;
  res.size=bigsize;
  res.total=0;
  res.makenode=makenode;
  res.compare=compare;
  res.entries=(entry*)malloc(sizeof(entry)*bigsize);
}
void addentry(void *key,void *value,symboltable *book)
{
  if(book->total==book->size)
    {
      book->size +=minisize;
      book->entries=(entry*)realloc(book->entries,sizeof(book->entries)*book->size);
    }
  entry *add=book->entries;
  add[book->total]=book->makenode(key,value);
  (book->total)++;
}
void dropentry(symboltable *book)
{
  if(book->entries!=NULL)
    {
      entry *delete=book->entries;
      int i;
      for(i=0;i<book->total;i++)
	{
	  free(delete->key);
	  free(delete->value);
	  delete++;
	}
      free(book->entries);
    }
  book->total=0;
  book->size=bigsize;
  book->entries=NULL;
}
entry *getentry(void *key,symboltable book)
{
  int i;
  entry *res=book.entries;
  for(i=0;i<book.total;i++)
    {
      if(strcmp((char*) key,(char*) res->key)==0)
	return  res;
      res++;
    }
  return NULL;
}

void switch_case(int *i)
{
  printf("------menu-----\n");
  printf("1.them phan tu.\n");
  printf("2.hien thi danh sach.\n");
  scanf("%d",&*i);
  switch(*i)
    {
    case 1:
      {
      }
    case 2:
      {
      }
    }
}

void main()
{
  int i;
  switch_case(&i);
}
