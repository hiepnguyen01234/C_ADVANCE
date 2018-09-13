#include"hambai3.h"

void readfile()
{
  int i,j;
  char s[31];
  FILE *fptr1;
  char filename1[]="dulieu.txt";
  if((*fptr1=fopen(filename1,"r"))==NULL)
    {
      printf("can't open file %s.",filename1);
      return;
    }
  while(!feof(fptr1))
    {
      if(fscanf(fptr1,"s",s)==1)
	{
     
	}
    }
  fclose(fptr1);
}

void switch_case()
{
  void switch_(int *n)
  {
    printf("-----menu-----\n");
    printf("1.mang luoi nha ga.\n");
    printf("2.tim kiem ga lien ke.\n");
    printf("3.thoat.\n");
    scanf("%d",&*n);
    switch(*n)
      {
      case 1:
	{
	  break;
	}
      case 2:
	{
	  break;
	}
      case 3:
	{
	  break;
	}
      }
  }

  int n=1;
  while(n!=3)
    {
      if((n>3)||(n<1))
	{
	  printf("nhap lai.\n");
	  switch_(&n);
	}
      else
	switch_(&n);
    }
}
