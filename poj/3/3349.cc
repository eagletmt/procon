#include <cstdio>
#include <cstdlib>
#include <algorithm>
using namespace std;

static int cmp(const int *a, const int *b)
{
  for (int i = 0; i < 6; i++) {
    if (a[i] < b[i]) {
      return -1;
    } else if (a[i] > b[i]) {
      return 1;
    }
  }
  return 0;
}

static int compare(const void *x, const void *y)
{
  const int *a = (int *)x;
  const int *b = (int *)y;
  return cmp(a, b);
}

static void normalize(int r[6], int a[6])
{
  copy(a, a+6, r);
  for (int i = 0; i < 6; i++) {
    if (cmp(a, r) < 0) {
      copy(a, a+6, r);
    }
    reverse(a, a+6);
    if (cmp(a, r) < 0) {
      copy(a, a+6, r);
    }
    reverse(a, a+6);
    rotate(a, a+1, a+6);
  }
}

int main()
{
  static int snows[100000][6];
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N; i++) {
    int a[6];
    for (int j = 0; j < 6; j++) {
      scanf("%d", &a[j]);
    }
    normalize(snows[i], a);
  }
  qsort(snows, N, sizeof *snows, compare);
  for (int i = 0; i < N-1; i++) {
    if (cmp(snows[i], snows[i+1]) == 0) {
      puts("Twin snowflakes found.");
      return 0;
    }
  }
  puts("No two snowflakes are alike.");
  return 0;
}