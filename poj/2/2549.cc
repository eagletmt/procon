#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

struct less_first
{
  bool operator()(const pair<ll, int>& x, const pair<ll, int>& y) const
  {
    return x.first < y.first;
  }
};

int N, M;

bool ok(const pair<ll, int> *a, ll x, int i, int j)
{
  const pair<ll, int> *r = lower_bound(a, a+M, make_pair(x, -1), less_first());
  if (r == a+M || r->first != x) {
    return false;
  }
  const int k = r->second / N;
  const int l = r->second % N;
  return i != k && i != l && j != k && j != l;
}

int main()
{
  while (scanf("%d", &N) != EOF && N != 0) {
    static const int MAXN = 1000;
    static ll s[MAXN];
    for (int i = 0; i < N; i++) {
      scanf("%lld", &s[i]);
    }
    M = 0;
    static pair<ll, int> a[MAXN * (MAXN-1) / 2];
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        a[M++] = make_pair(s[i] + s[j], i*N + j);
      }
    }
    sort(a, a + M);

    static const ll INF = 1LL<<50;
    ll ans = -INF;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < i; j++) {
        if (ok(a, s[i] - s[j], i, j)) {
          ans = max(ans, s[i]);
        }
        if (ok(a, s[j] - s[i], i, j)) {
          ans = max(ans, s[j]);
        }
      }
    }
    if (ans == -INF) {
      puts("no solution");
    } else {
      printf("%lld\n", ans);
    }
  }
  return 0;
}