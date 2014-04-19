#include <iostream>
#include <vector>
using namespace std;

bool valid(int s, int M)
{
  for (int i = 0; i < M-1; i++) {
    if ((s & (1<<i)) && (s & (1<<(i+1)))) {
      return false;
    }
  }
  return true;
}

int main()
{
  static const int MOD = 100000000;
  int N, M;
  cin >> N >> M;
  vector<unsigned> grid(N, 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      unsigned x;
      cin >> x;
      grid[i] = (grid[i]<<1) | x;
    }
  }

  vector<int> dp(1<<M, 0);
  for (int s = 0; s < (1<<M); s++) {
    const int t = s & grid[0];
    if (t == s) {
      for (int u = 0; u < (1<<M); u++) {
        if ((u & s) == u && valid(u, M)) {
          dp[s] = (dp[s] + 1) % MOD;
        }
      }
    } else {
      dp[s] = dp[t];
    }
  }
  vector<int> dp_next(1<<M);
  for (int i = 1; i < N; i++) {
    fill(dp_next.begin(), dp_next.end(), 0);
    for (int s = 0; s < (1<<M); s++) {
      const int t = s & grid[i];
      if (s != 0 && t == s) {
        for (int u = 0; u < (1<<M); u++) {
          if ((u & s) == u && valid(u, M)) {
            dp_next[s] = (dp_next[s] + dp[(~u)&((1<<M)-1)]) % MOD;
          }
        }
      } else if (t != 0) {
        dp_next[s] = dp_next[t];
      } else {
        dp_next[s] = dp[(1<<M)-1];
      }
    }
    swap(dp, dp_next);
  }
  cout << dp[(1<<M)-1] << endl;
  return 0;
}