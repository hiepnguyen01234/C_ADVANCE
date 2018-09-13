#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define bigsize 100
#define minisize 10

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
}symboltable;

void createsymboltable(void *name,void  *mssv,symboltable *res)
{
  res->entries=(entry*)malloc(sizeof(entry));
  res->size=bigsize;
  strcpy((char*)res->entries->value,(char*)name);
  strcpy((char*)res->entries->key,(char*)mssv);
  res->total ++;
}

int main()
{
  symboltable *book;
  book->entries=(entry*)malloc(sizeof(entry));//chuong trinh bi dung o day.

  createsymboltable("teo","12",book);
  return 0;
}
