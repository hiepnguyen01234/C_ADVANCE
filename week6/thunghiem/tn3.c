#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"thuvien.h"

int main()
{
  FILE *fptr1;
  char s[31];
  char filename1[]="dulieu.txt";
  if((fptr1=fopen(filename1,"r"))==NULL)
    {
      printf("khong the mo %s.\n",filename1);
      exit(1);
    }
  sscanf(fptr1,"%s",s);
  printf("ngooif been hieen ngawms las rowi nhinf nuj hoa ddax ph");
  fclose(fptr1);
  return 0;
}
