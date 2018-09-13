#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../libfdr/jrb.h"
#include"../libfdr/fields.h"
#define csv "data.txt"

typedef struct 
{
  char *name;
  char *tel;
}person;

person *get_data_from_file(FILE *fp,int size);
void add_to_tree(JRB *t,person *arr,int size);

person *get_data_form_file(FILE *fp,int size)
{
  person *ret=(person*)malloc(sizeof(person)*size);
  if(ret==NULL)
    {
      fprintf(stderr,"error %s:%d.\n",_FILE_,_LINE_);
      exit(1);
    }
  int i;
  char name[31];
  char tel[31];
  for(i=0;i<size;i++)
    {
      fscanf(fp,"%[^|]|%[^|]|%*[^|]|%*[^\n]\n",name,tel);    //de lam gi.

      ret[i].name=(char*)malloc(strlen(name)+1);
      ret[i].tel=(char*)malloc(strlen(tel)+1);
      if(ret[i].name==NULL||ret[i].tel==NULL)
	{
	  fprintf(stderr,"error %s:%d\n",_FILE_,_LINE_);
	  exit(1);
	}
      strcpy(ret[i].name,name);
      strcpy(ret[i].tel,tel);
    }
  return ret;
}
void add_to_tree(JRB *t,person *arr,int size)
{
  if(t==NULL)
    {
      fprintf(stderr,"error %s:%d.\n",_FILE_,_LINE_);
      exit(1);
    }
  int i;
  for(i=0;i<size;i++)
    {
      jrb_insert_str(*t,arr[i].name,new_jval_s(arr[i].tel));
    }
}
int count_line(FILE *fp)
{
  char s[100];
  int count=0;
  while(fgets(s,100,fp)!=NULL)
    {
      count++;
    }
  rewind(fp);
  return count;
}

void switch_case(int *n)
{
  printf("---menu---\n");
  printf("1.insert:nhap tu ban phim so nguyen va chen vao cay.\n");
  printf("2.display:hien thi tat ca cac so nguyen da nhap.\n");
  printf("3.destroy:huy bo vung nho cap phat cho cac nut tren cay.\n");
  scanf("%d",&*n);
  JRB t;
  t=make_jrb();
  switch(*n)
    {
    case 1:
      {
	FILE *fin=fopen(csv,"r");
	if(fin==NULL)
	  {
	    fprntf("can't open file :%s\n",csv);
	    exit(1);
	  }
	int size=count_lin(fin);
	person *arr=get_data_from_file(fin,size);
	add_to_size(&t,arr,size);
	free(arr);
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

main()
{
  int n=1;
  while((n>=1)||(n<=3))
    {
      switch_case(&n);
    }
}
