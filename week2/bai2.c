#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#define ARR_SIZE 100

typedef union {
  int i;
  long l;
  float f;
  double d;
  void *v;
  char *s;
  char c;
} Jval;

Jval new_jval_i(int i) { Jval j; j.i = i; return j; }
Jval new_jval_l(long l) { Jval j; j.l = l; return j; }
Jval new_jval_f(float f) { Jval j; j.f = f; return j; }
Jval new_jval_d(double d) { Jval j; j.d = d; return j; }
Jval new_jval_v(void *v) { Jval j; j.v = v; return j; }

int jval_i(Jval j) { return j.i; }
long jval_l(Jval j) { return j.l; }
float jval_f(Jval j) { return j.f; }
double jval_d(Jval j) { return j.d; }
void *jval_v(Jval j) { return j.v; }

int compare_i(Jval* a, Jval* b) {
  if (jval_i(*a) == jval_i(*b)) return 0;
  if (jval_i(*a) < jval_i(*b)) return -1;
  else return 1;
}

void jswap(Jval *a, Jval *b){
  Jval temp = *a;
  *a = *b;
  *b = temp;
}

void sort_gen_jval(Jval a[], int l, int r, int (*compare)(Jval*, Jval*)){
  if (r < l) return;
  int i = l-1, j = r;
  int p = l-1, q = r;
  while(1) {
    while ((compare(&a[++i], &a[r])) < 0);
    while (compare(&a[r], &a[--j]) < 0) if (j == l) break;
    if (i >= j) break;
    jswap(&a[i], &a[j]);
    if (compare(&a[i], &a[r]) == 0) {
      p++;
      jswap(&a[p], &a[i]);
    }
    if (compare(&a[j], &a[r]) == 0) {
      q--;
      jswap(&a[j], &a[q]);
    }
  }
  jswap(&a[i], &a[r]);
  j = i-1;
  int k;
  for (k = l; k < p; k++, j--)
    jswap(&a[k], &a[j]);
  i = i+1;
  for (k = r-1; k > q; k--, i++)
    jswap(&a[i], &a[k]);
  sort_gen_jval(a, l, j, compare);
  sort_gen_jval(a, i, r, compare);
}

void printarr(int a[], int n)
{
  int i;
  for (i = 0; i < n; ++i)
    printf("%d  ", a[i]);
  printf("\n");
}

int *createArray(int size){
  int *arr;
  arr = (int*)malloc(size * sizeof(int));
  srand(time(NULL));
  int i;
  for (i = 0; i < size; i++)
    {
      arr[i] = rand() % size + 1;
    }
  return arr;
}

Jval *create_array_i(int size) {
  Jval *arr = (Jval*)malloc(sizeof(Jval) * size);
  srand(time(NULL));     //?
  int i;
  for (i = 0; i < size; i++) arr[i] = new_jval_i(rand() % ARR_SIZE + 1);
  return arr;
}

void printJval_i(Jval a[], int n) {
  int i;
  for (i = 0; i < n; i++)
    printf("%d  ", a[i].i);
  printf("\n");	
}

int main()
{
  time_t start,end;
  start = clock();
  Jval *a = create_array_i(ARR_SIZE);
  sort_gen_jval(a, 0, ARR_SIZE - 1, compare_i);
  end = clock();
  float interval = (float)(end - start)/CLOCKS_PER_SEC;
  printJval_i(a, ARR_SIZE);
  printf("Completed after: %.20fs\n", interval);
  free(a);
  return 0;
}
