#include <cstdio>
#include <algorithm>
using namespace std;

struct cmp
{
  bool operator()(const pair<int,int>& l, const pair<int,int>& r) const
  {
    return static_cast<double>(l.second)/l.first > static_cast<double>(r.second)/r.first;
  }
};

int main()
{
  int N;
  scanf("%d", &N);
  static const int M = 100000;
  static pair<int,int> a[M];
  int sum = 0;
  for (int i = 0; i < N; i++) {
    scanf("%d %d", &a[i].first, &a[i].second);
    sum += a[i].second;
  }
  sort(a, a+N, cmp());

  long long ans = 0LL;
  for (int i = 0; i < N; i++) {
    ans += 2LL * (sum - a[i].second) * a[i].first;
    sum -= a[i].second;
  }
  printf("%lld\n", ans);
  return 0;
}