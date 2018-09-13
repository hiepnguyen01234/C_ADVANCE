#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../b_tree/inc/btree.h"

typedef struct
{
  char hoten[31];
  int maso;
}sv;

int main()
{
  BTA *sinhvien;
  sv teo;
  while(getchar()!='\n');
  printf("nhap ho ten:");
  gets(teo.hoten);
  printf("nhap ma so sinh vien:");
  scanf("%d",&teo.maso);

  sinhvien=btopn("sinhvien",0,0);//mofile b_tree.
  if(sinhvien!=NULL) printf("file will be open.\n");
  if(sinhvien==NULL)
    {
      sinhvien=btcrt("sinhvien",0,0);//taofile b_tree.
      printf("file will be create.\n");
    }
  if(btins(sinhvien,teo.maso,(char*)&teo.hoten,sizeof(sv))==0)//tao gia tri cho nut moi.
    printf("cap nhat thanh cong.\n");
  else printf("symtem defaut.\n");
  btcls(sinhvien);//dongfile b_tree.
  return 0;
}
