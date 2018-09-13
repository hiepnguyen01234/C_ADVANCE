#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"capphatdong.h"

int main()
{
  symboltable book;
  entry *found;
  char name[25];
  book=createsymboltable(makephone,comparephone);
  addentry("haha","123",&book);

  printf("name want to find:");
  scanf("%s",name);
  found=getentry(name,book);
  if(found ==NULL)
    printf("this name was empty.\n");
  else 
    printf("the number of %s is: %s\n",(char*)found->key,(char*)found->value);
  dropsymboltable(&book);
  return 0;
}
