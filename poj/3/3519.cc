#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int N, T, L, B;
  while (scanf("%d %d %d %d", &N, &T, &L, &B) == 4 && N != 0) {
    vector<bool> lose(N+1, false), back(N+1, false);
    for (int i = 0; i < L; i++) {
      int l;
      scanf("%d", &l);
      lose[l] = true;
    }
    for (int i = 0; i < B; i++) {
      int b;
      scanf("%d", &b);
      back[b] = true;
    }

    vector<double> dp(N+1, 0.0), dp_wait(N+1, 0.0);
    dp[0] = 1.0;
    double ans = 0.0;
    for (int t = 0; t < T; t++) {
      vector<double> dp_next(N+1, 0.0), dp_wait_next(N+1, 0.0);
      for (int i = 0; i < N; i++) {
        for (int j = 1; j <= 6; j++) {
          int n = i + j;
          if (n > N) {
            n = N - (n - N);
          }
          if (back[n]) {
            dp_next[0] += dp[i] / 6.0;
          } else if (lose[n]) {
            dp_wait_next[n] += dp[i] / 6.0;
          } else {
            dp_next[n] += dp[i] / 6.0;
          }
        }
        dp_next[i] += dp_wait[i];
      }
      ans += dp_next[N];
      dp_next[N] = 0.0;
      swap(dp, dp_next);
      swap(dp_wait, dp_wait_next);
    }
    printf("%.6f\n", ans);
  }
  return 0;
}