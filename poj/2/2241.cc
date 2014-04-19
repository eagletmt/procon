#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

struct triple
{
  int w, d, h;
  triple(int a, int b, int c) : w(a), d(b), h(c) {}
  bool operator>(const triple& that) const
  {
    if (w != that.w) {
      return w > that.w;
    } else if (d != that.d) {
      return d > that.d;
    } else {
      return h > that.h;
    }
  }
};

int main()
{
  int N;
  for (int Ti = 1; scanf("%d", &N) != EOF && N != 0; ++Ti) {
    vector<triple> v;
    for (int i = 0; i < N; i++) {
      int a[3];
      scanf("%d %d %d", a, a+1, a+2);
      sort(a, a+3);
      do {
        v.push_back(triple(a[0], a[1], a[2]));
      } while (next_permutation(a, a+3));
    }
    sort(v.begin(), v.end(), greater<triple>());
    int ans = 0;
    const int M = v.size();
    vector<int> dp(M, 0);
    for (int i = 0; i < M; i++) {
      dp[i] = v[i].h;
      for (int j = 0; j < i; j++) {
        if (v[j].w > v[i].w && v[j].d > v[i].d) {
          dp[i] = max(dp[i], dp[j] + v[i].h);
        }
      }
      ans = max(ans, dp[i]);
    }
    printf("Case %d: maximum height = %d\n", Ti, ans);
  }
  return 0;
}