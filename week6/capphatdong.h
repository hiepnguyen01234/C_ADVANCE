#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct 
{
  void *key;
  void *value;
}entry;
typedef struct 
{
  entry *entries;
  int size;
  int total;
  entry (*makenode)(void *,void *);     //?
  int (*compare)(void *,void *);        //?
}symboltable;

symboltable createsymboltable(entry (*makenode)(void *,void *),int (*compare)(void *,void *));
void dropsymboltable(symboltable *tab);
void addentry(void *key,void *value,symboltable *book);
entry *getentry(void *key,symboltable book);
entry makephone(void *name,void *phone);
int comparephone(void *key1,void *key2);
