#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<vector<pair<int,int> > > g(N);
    for (int i = 0; i < N; i++) {
      int k;
      cin >> k;
      for (int j = 0; j < k; j++) {
        int c, d;
        cin >> c >> d;
        g[i].push_back(make_pair(c, d));
      }
    }

    vector<vector<vector<int> > > dp(N);
    for (int i = 0; i < N; i++) {
      dp[i].resize(g[i].size(), vector<int>(M+1, numeric_limits<int>::max()/2));
    }
    for (int i = 0; i < g[0].size(); i++) {
      dp[0][i][0] = 0;
    }
    for (int i = 0; i < g[1].size(); i++) {
      dp[1][i][1] = 0;
    }

    int ans = numeric_limits<int>::max();
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < g[i].size(); j++) {
        for (int m = 0; m <= M; m++) {
          if (i+1 == N) {
            ans = min(ans, dp[i][j][m]);
          } else {
            for (int k = 0; k < g[i+1].size(); k++) {
              dp[i+1][k][m] = min(dp[i+1][k][m], dp[i][j][m] + (g[i][j].second + g[i+1][k].second)*abs(g[i][j].first - g[i+1][k].first));
            }

            if (i < N-1 && m < M) {
              if (i+2 == N) {
                ans = min(ans, dp[i][j][m]);
              } else {
                for (int k = 0; k < g[i+2].size(); k++) {
                  dp[i+2][k][m+1] = min(dp[i+2][k][m+1], dp[i][j][m] + (g[i][j].second + g[i+2][k].second)*abs(g[i][j].first - g[i+2][k].first));
                }
              }
            }
          }
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
