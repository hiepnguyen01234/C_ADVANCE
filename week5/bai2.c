#include<stdio.h>
#include<stdlib.h>

#include"../b_tree/inc/btree.h"

typedef struct
{
  char phonenumber[31];
  char name[31];
}address;

void createbook(BTA *book)
{
  if(book!=NULL) printf("doc file thanh cong.\n");
  if(book==NULL)//neukhongco 
    {
      book=btcrt("phonebook",0,0);//khoitao file btree  Phonebook: BTA *btcrt(char *fid,int nkeys,int shared);

      printf("file will be create .\n\n");
    }
}
void insertnode(BTA *book,address node[])
{
  int i;
  for(i=0;i<2;i++)
    {
      while(getchar()!='\n');
      printf("name %d:",i);
      gets(node[i].name);
      printf("phonenumber %d:",i);
      scanf("%s",node[i].phonenumber);

      if(btins(book,node[i].name,node[i].phonenumber,sizeof(node[i].phonenumber))==0) //khong the ep kieu (char*)&node[i].phonenumber
	//chen mot khoa: int btins(BTA *btact,char *key,char *data,int dsize);

	{
	  printf(" insert .\n");
	}
      else
	{
	  printf("cannot insert .\n");
	}
    }
}
void mfflush()
{
  int ch;
  while((ch=getchar()) && ch!='\n' && ch != EOF);
}

void switch_case(int *n)
{
  printf("---menu---\n");
  printf("1.them thong tin lien lac moi.\n");
  printf("2.tim kiem theo ten.\n");
  printf("3.hien thi toan bo danh ba.\n");
  printf("4.xoa mot thong tin lien lac.\n");
  printf("5.thoat.\n");
  scanf("%d",&*n);
  BTA *book;
  address node[3];
  switch(*n)
    {
    case 1:
      {
	book=btopn("phonebook",0,0);    //mo file btree phonebook: BTA *btopen(char *fid,int mode,int shared);
	createbook(book);
	insertnode(book,node);
	btcls(book); 
	break;
      }
    case 2:
      {
	char ten[31];
	char so[31];
	int n;
	book=btopn("phonebook",0,0);    //mo file btree phonebook: BTA *btopen(char *fid,int mode,int shared);
	printf("enter name you want to find:");
	while(getchar()!='\n');
	gets(ten);
	if(btsel(book,ten,so,sizeof(so),&n)==0) 
	  printf("phonnumber: %s\n",so);
	else printf("can not search.\n");
	btcls(book); 
	break;
      }
    case 3:
      {
	char ten[31];
	char so[31];
	book=btopn("phonebook",0,0);    //mo file btree phonebook: BTA *btopen(char *fid,int mode,int shared);
	btpos(book,ZSTART);//cankhoitaodedoc'btree'
	printf("the table of phonebook:\n");
	while(1)
	  {
	    if(btseln(book,ten,so,sizeof(so),&n)==QNOKEY)//doc'btree'vaothamsodencuoi
	      break;
	    printf("%s  %s\n",ten,so);
	  }
	btcls(book); 
	break;
      }
    case 4:
      {
	char ten[31];
	book=btopn("phonebook",0,0);    //mo file btree phonebook: BTA *btopen(char *fid,int mode,int shared);
	printf("enter name you want to delete all of information:");
	while(getchar()!='\n');
	gets(ten);
	if(btdel(book,ten)==0) 
	  printf("xoa thanh cong.\n");
	else printf("error_cannot delete.\n");
	btcls(book); 
	break;
      }
    case 5:
      {
	break;
      }
    }
}

int  main()
{
  int n=1;
  while(n!=5)
    {
      if((n>5)||(n<1))
	{
	  printf("chon lai.\n");
	  switch_case(&n);
	}
      else switch_case(&n);
    }
  return 0;
}
