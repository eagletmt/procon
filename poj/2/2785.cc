#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  static const int M = 4000;
  int N;
  scanf("%d", &N);
  static long long a[M], b[M], c[M], d[M];
  for (int i = 0; i < N; i++) {
    scanf("%lld %lld %lld %lld", &a[i], &b[i], &c[i], &d[i]);
  }

  static long long cd[M*M];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cd[i*N+j] = -c[i]-d[j];
    }
  }
  sort(cd, cd + N*N);
  long long ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      pair<long long *,long long *> p = equal_range(cd, cd + N*N, a[i]+b[j]);
      ans += distance(p.first, p.second);
    }
  }
  printf("%lld\n", ans);
  return 0;
}
