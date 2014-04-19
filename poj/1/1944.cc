#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, P;
  scanf("%d %d", &N, &P);
  static const int M = 10000;
  static int from[M], to[M];
  for (int i = 0; i < P; i++) {
    scanf("%d %d", &from[i], &to[i]);
    --from[i];  --to[i];
    if (from[i] > to[i]) {
      swap(from[i], to[i]);
    }
  }

  int ans = 10000;
  for (int i = 0; i < N; i++) {
    // do not use the edge: (i) - (i+1)
    static int v[1000];
    fill_n(v, N, 0);
    for (int j = 0; j < P; j++) {
      if (from[j] <= i && i+1 <= to[j]) {
        ++v[0];
        --v[from[j]];
        ++v[to[j]];
      } else {
        ++v[from[j]];
        --v[to[j]];
      }
    }
    int c = 0;
    int acc = 0;
    for (int j = 0; j < N; j++) {
      acc += v[j];
      if (acc > 0) {
        ++c;
      }
    }
    ans = min(ans, c);
  }
  printf("%d\n", ans);
  return 0;
}