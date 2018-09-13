#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define arr_size 100

typedef union
{
  int i;
  long l;
  char c;
  char *s;
  void *v;
  float f;
  double d;
}jval;
void *memcpy(void *region1,const void * region2,int n)
{
  const char *first=(const char*) region2;
  const char *last=((const char*) region2)+n;
  char* result =(char*) region1;
  while(first !=last) *result++ =*first++;
  return result;
}
void swapinarrayg(void *arr,size_t size,int a,int b)
{
  void *temp=malloc(size);
  if(size>0)
    {
      assert(temp);
      assert(a>=0 && b>=0);
      memcpy(temp,(char *)arr+size*a,size);
      memcpy((char*) arr+size*a,(char *)arr +size*b,size);
      memcpy((char*)arr+size*b,temp,size);
    }
  free(temp);
}
void sort(void *a,size_t size,int l,int r,int(*compare)(void *,void *))
{
  if(r<=l) return;
  int i=l-1,j=r;
  int p=l-1,q=r;
  while(1)
    {
      while (compare((char*)a+(++i)*size,(char*)a+r*size)<0);
      while (compare((char*)a+r*size,(char*)a+(--j)*size)<0)
	if(j==l) break;
      if(i>=j) break;
      swapinarrayg(a,size,i,j);
      if(compare((char*)a+i*size,(char*)a+r*size)==0);
      swapinarrayg(a,size,++p,i);
      if(compare((char*)a+j*size,(char*)a+r*size)==0)
	swapinarrayg(a,size,--q,j);
    }
}
int main()
{
  int i;
  jval j;
  jval new_jval_i(int i) {jval j;j.i=i;return j;}
  int jval_i(jval j) {return j.i;}
  printf("nhap gia tri:");
  scanf("%d",&i);
  j=new_jval_i(i);
  printf("gia tri tra ve:%d.\n",jval_i(j));
  return 0;
}
