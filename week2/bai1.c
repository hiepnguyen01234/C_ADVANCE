#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define max 100

int *createarray(int size)
{
  int *a;
  a=(int *)malloc(sizeof(int)*size);
  return a;
}
void* memcpy(void* region1, const void* region2, size_t n) {      //?(size_t)
  const char* first = (const char*) region2;                  //?
  const char* last = ((const char*) region2) + n;             //?
  char* result = (char*) region1;
  while (first != last) *result++ = *first++;
  return result;
}
int int_compare(void *x, void *y) {
  int m, n;
  m = *((int*)x);
  n = *((int*)y); 
  if ( m == n ) return 0;
  return m > n ? 1: -1;
}
void SwapInArrayG(void * arr, size_t size, int a, int b) {
  void * temp = malloc(size);          //?
  if (size > 0) {
    assert(temp);           //?(assert)
    assert(a >= 0 && b >= 0);
    memcpy(temp, (char *)arr + size*a, size);
    memcpy((char *)arr + size*a, (char *)arr + size*b, size);
    memcpy((char *)arr + size*b, temp, size);
  }
  free(temp);  
}

void sort(void* a, size_t size, int l, int r, 
	  int (*compare)(void*, void*)) {
  if (r <= l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1)	{
    while ( compare((char*)a+(++i)*size, (char*)a+r*size) < 0 );
    while (compare((char*)a+r*size, (char*)a+(--j)*size) < 0 )
      if (j == l) break;
    if (i >= j) break;
    SwapInArrayG(a, size, i, j);
    if (compare((char*)a+i*size, (char*)a+r*size)==0)
      SwapInArrayG(a, size, ++p, i);
    if (compare((char*)a+j*size, (char*)a+r*size)==0)
      SwapInArrayG(a, size, --q, j);
  }
  SwapInArrayG(a, size, i, r);
  j = i - 1;
  i = i + 1;
  int k;
  for (k = l ; k <= p; k++) SwapInArrayG(a, size, k, j--);
  for (k = r-1; k >= q; k--) SwapInArrayG(a, size, k, i++);
  sort(a, size, l, j, compare);
  sort(a, size, i, r, compare);
}

int main()
{
  int *a;
  int i;
  time_t start,end;
  float interval;

  a=createarray(max);
  for(i=0;i<max;++i)
    a[i]=rand()%100;
  puts("\n");
  for(i=0;i<max;++i)
    printf("%-5d",a[i]);
  puts("\n");

  start=clock();
  sort(a,sizeof(int),0,max,int_compare);
  end=clock();
  interval=(float)(end-start);

  for(i=0;i<max;++i)
    printf("%-5d",a[i]);
  printf("\n\ntime:%.10f\n",interval);
  free(a);
  return 0;
}
