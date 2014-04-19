#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int sqr(int x) { return x*x; }

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    vector<int> cs(M);
    for (int i = 0; i < M; i++) {
      scanf("%d", &cs[i]);
    }

    static long long dp[20000+1][256];
    static const long long INF = 1LL<<50;
    fill_n(dp[0], 256, INF);
    dp[0][128] = 0;
    for (int i = 1; i <= N; i++) {
      int x;
      scanf("%d", &x);
      fill_n(dp[i], 256, INF);
      for (int j = 0; j < 256; j++) {
        for (int k = 0; k < M; k++) {
          int y = j + cs[k];
          if (y < 0) {
            y = 0;
          } else if (y > 255) {
            y = 255;
          }
          dp[i][y] = min(dp[i][y], dp[i-1][j] + sqr(y - x));
        }
      }
    }
    printf("%lld\n", *min_element(dp[N], dp[N]+256));
  }
  return 0;
}
