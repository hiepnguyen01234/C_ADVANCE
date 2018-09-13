#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"capphatdong.h"

#define bigsize 100
#define minisize 10

entry makephone(void *name,void *phone)
{
  entry res;
  res.key=strdup((char*)name);
  res.value=strdup((char*)phone);
  return res;
}
int comparephone(void *key1,void *key2)
{
  return strcmp((char*)key1,(char *)key2);
}


symboltable createsymboltable(entry (*makenode)(void *,void *),int (*compare)(void *,void *))
{
  symboltable res;
  res.size=bigsize;
  res.total=0;
  res.makenode=makenode;
  res.compare=compare;
  res.entries=(entry *)malloc(sizeof(entry) * res.size);
  return res;
}
void dropsymboltable(symboltable *tab)
{
  if(tab==NULL)
    exit(1);
  if(tab->entries != NULL)
    {
      entry *to_free_entry = tab->entries;
      int i=0;
      while(i<tab->total)
	{
	  free(to_free_entry->key);
	  free(to_free_entry->value);
	  to_free_entry++;
	  i++;
	}
      free(tab->entries);      //?(xoahetphanturoi,saophaifree)
    }
  tab->total=0;
  tab->size=bigsize;           //?(muc dich de lam gi.)
  tab->entries=NULL;
}
void addentry(void *key,void *value,symboltable *book)
{
  if(key==NULL || book==NULL)
    exit(1);
  if(getentry(key,*book)!=NULL)
    return;
  if(book->entries==NULL)
    exit(1);
  if(book->total==book->size)
    {
      (book->size) += minisize;                 //?
      (book->entries) = (entry*)realloc(book->entries,sizeof(entry)*(book->size));
      if(book->entries==NULL)
	exit(1);
    }
  entry *add=book->entries;
  add[book->total]=book->makenode(key,value);
  (book->total)++;
}
entry *getentry(void *key,symboltable book)
{
  entry *res=book.entries;
  int i=0;
  while(i<book.total)
    {
      if(book.compare(res->key,key) == 0)
	return res;
      res++;
      i++;
    }
  return NULL;
}
