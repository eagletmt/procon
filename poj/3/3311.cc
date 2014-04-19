#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  while (cin >> n && n != 0) {
    vector<vector<int> > g(n+1, vector<int>(n+1));
    for (int i = 0; i < n+1; i++) {
      for (int j = 0; j < n+1; j++) {
        cin >> g[i][j];
      }
    }

    for (int i = 0; i < n+1; i++) {
      for (int j = 0; j < n+1; j++) {
        for (int k = 0; k < n+1; k++) {
          g[i][j] = min(g[i][j], g[i][k] + g[k][j]);
        }
      }
    }

    vector<vector<int> > dp(1<<(n+1), vector<int>(n+1, 1000000));
    for (int i = 0; i < n+1; i++) {
      dp[1<<i][i] = g[0][i];
    }
    for (int s = 1; s < (1<<(n+1)); s++) {
      for (int i = 0; i < n+1; i++) {
        if ((s & (1<<i)) == 0) { continue; }
        for (int j = 0; j < n+1; j++) {
          if ((s & (1<<j)) != 0) { continue; }
          const int t = s | (1<<j);
          dp[t][j] = min(dp[t][j], dp[s][i] + g[i][j]);
        }
      }
    }

    int ans = dp[(1<<(n+1))-1][0];;
    cout << ans << endl;
  }
  return 0;
}