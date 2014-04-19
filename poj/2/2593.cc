#include <cstdio>
#include <vector>
#include <limits>
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) != EOF && n != 0) {
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      scanf("%d", &v[i]);
    }

    vector<int> dp(n);
    dp.front() = v.front();
    int s = max(dp.front(), 0);
    for (int i = 1; i < n; i++) {
      s += v[i];
      dp[i] =  max(dp[i-1], s);
      s = max(s, 0);
    }

    int t = numeric_limits<int>::min();
    s = 0;
    int ans = numeric_limits<int>::min();
    for (int i = n-1; i > 0; i--) {
      s += v[i];
      t = max(t, s);
      s = max(s, 0);
      ans = max(ans, dp[i-1] + t);
    }
    printf("%d\n", ans);
  }
  return 0;
}
