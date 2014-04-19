#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int C;
  scanf("%d", &C);
  while (C-- > 0) {
    int D, N;
    scanf("%d %d", &D, &N);
    static int a[50000];
    for (int i = 0; i < N; i++) {
      long long x;
      scanf("%lld", &x);
      a[i] = x % D;
    }
    static long long cnt[1000000];
    fill_n(cnt, D, 0LL);
    int sum = 0;
    ++cnt[0];
    for (int i = 0; i < N; i++) {
      sum = (sum + a[i]) % D;
      ++cnt[sum];
    }
    long long ans = 0LL;
    for (int i = 0; i < D; i++) {
      ans += cnt[i] * (cnt[i]-1LL) / 2LL;
    }
    printf("%lld\n", ans);
  }
  return 0;
}
