#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include"../libfdr/jrb.h"

void switch_case(int *n)
{
  printf("---menu---\n");
  printf("1.insert.\n");
  printf("2.desplay.\n");
  printf("3.destroy.\n");
  scanf("%d",&*n);
  JRB cret;
  cret=make_jrb();
  switch(*n)
    {
    case 1:
      {
	jrb_insert_int(cret,123,123);
	break;
      }
    case 2:
      {
	printf("ngoi ben hien ngam la roi nhin nu hoa da phai sac mau con gio ve canh hoa tan lang tham rung roi theo gio bay de duoc bat keo ve noi nay ngam hoa roi");
	break;
      }
    case 3:
      {
	break;
      }
    }
}

int main()
{
  int n=1;
  while((n>=1)&&(n<=3))
    {
      switch_case(&n);
    }
  return 0;
}
