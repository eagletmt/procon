#include <stdio.h>
static inline int min(int a, int b) { return a > b ? b : a; }
static inline int max(int a, int b) { return a > b ? a : b; }

int main(void)
{
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    int L, M;
    scanf("%d%d", &L, &M);
    int x = 0, y = 0, i;
    for (i = 0; i < M; i++) {
      int a;
      scanf("%d", &a);
      x = max(x, min(a, L-a));
      y = max(y, max(a, L-a));
    }
    printf("%d %d\n", x, y);
  }
  return 0;
}