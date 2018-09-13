#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define max 100

void swap(int *a,int *b)
{
  int tmp=*a;
  *a=*b;
  *b=tmp;
}
void exch(int *array,int a,int b)
{
  int temp;
  temp=array[a];
  array[a]=array[b];
  array[b]=temp;
}
int partition(int a[],int low,int high)
{
  int pivot=a[high];
  int i=low-1;
  int j;
  for(j=low;j<=high-1;++j)
    if(a[j]<=pivot)
      {
	i++;
	swap(&a[i],&a[j]);
      }
  swap(&a[i+1],&a[high]);
  return i+1;
}
void sort2ways(int a[],int low,int high)
{
  int p;
  if(low<high)
    {
      p=partition(a,low,high);
      sort2ways(a,low,p-1);
      sort2ways(a,p+1,high);
    }
}
void sort3ways(int a[],int l,int r)
{
  if(r<=l) return;
  int i=l-1,p=i,j=r,q=j;
  while(1)
    {
      while(a[++i]<a[r]);
      while(a[r]<a[--j]) if (j==l) break;
      if(i>=j) break;
      exch(a,i,j);
      if(a[i]==a[r]) exch(a,++p,i);
      if(a[j]==a[r]) exch(a,--q,j);
    }
  exch(a,i,r);
  j=i-1;
  i=i+1;
  int k;
  for(k=l;k<=p;k++) exch(a,k,j--);
  for(k=r-1;k>=q;k--) exch(a,k,i++);
  sort3ways(a,l,j);
  sort3ways(a,i,r);
}

void main()
{
  int *a,*b;
  int i;
  float time1,time2;
  time_t start1,end1,start2,end2;

  a=(int *)malloc(sizeof(int)*max);
  b=(int *)malloc(sizeof(int)*max);
  for(i=0;i<max;i++)
    {
      a[i]=rand()%100;
      b[i]=a[i];
    }
  start1=clock();
  sort3ways(a,0,max);
  end1=clock();
  start2=clock();
  sort2ways(b,0,max);
  end2=clock();
  time1=(float) (end1-start1);
  time2=(float) (end2-start2);
  printf("time sort2ways: %.10f\n",time2);
  printf("time sort3ways: %.10f\n",time1);
  free(a);
  free(b);
}
