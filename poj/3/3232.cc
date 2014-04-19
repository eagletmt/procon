#include <cstdio>
#include <algorithm>
using namespace std;

bool ok(int ans, const int *a, int N, int M, int K)
{
  --K;
  const long long L = static_cast<long long>(ans) * min(M, N);
  long long l = 0;
  for (int i = 0; i < N; i++) {
    if (a[i] > ans) {
      int rest = a[i] - ans;
      int c = rest/K;
      if (rest % K != 0) {
        c++;
      }
      if (c > ans) {
        return false;
      }
      l += static_cast<long long>(c);
    }
  }
  return l <= L;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static int a[100000];
    for (int i = 0; i < N; i++) {
      scanf("%d", &a[i]);
    }
    int M, K;
    scanf("%d %d", &M, &K);

    if (K == 1) {
      printf("%d\n", *max_element(a, a+N));
      continue;
    }
    int lo = 1, hi = 100000000;
    while (lo < hi) {
      const int mid = (lo + hi)/2;
      if (ok(mid, a, N, M, K)) {
        hi = mid;
      } else {
        lo = mid+1;
      }
    }
    printf("%d\n", lo);
  }
  return 0;
}