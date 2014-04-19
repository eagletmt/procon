#include <iostream>
using namespace std;

static const int INF = 1000000;
int distS[200][200], distL[200][200];
int route[10000];
int dp[10000][200];

int main()
{
  int N, M;
  while (cin >> N >> M && !(N == 0 && M == 0)) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        distS[i][j] = distL[i][j] = INF;
      }
      distS[i][i] = distL[i][i] = 0;
    }

    for (int i = 0; i < M; i++) {
      int x, y, t;
      char sl;
      cin >> x >> y >> t >> sl;
      x--;  y--;
      if (sl == 'S') {
        distS[x][y] = distS[y][x] = t;
      } else {
        distL[x][y] = distL[y][x] = t;
      }
    }

    int R;
    cin >> R;
    for (int i = 0; i < R; i++) {
      cin >> route[i];
      route[i]--;
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          distS[i][j] = min(distS[i][j], distS[i][k] + distS[k][j]);
          distL[i][j] = min(distL[i][j], distL[i][k] + distL[k][j]);
        }
      }
    }

    for (int j = 0; j < N; j++) {
      dp[0][j] = distS[route[0]][j];
    }
    for (int i = 1; i < R; i++) {
      for (int j = 0; j < N; j++) {
        dp[i][j] = dp[i-1][j] + distL[route[i-1]][route[i]];
        for (int k = 0; k < N; k++) {
          dp[i][j] = min(dp[i][j], dp[i-1][k] + distL[route[i-1]][k] + distS[k][j] + distL[j][route[i]]);
        }
      }
    }

    int ans = INF;
    for (int i = 0; i < N; i++) {
      ans = min(ans, dp[R-1][i]);
    }
    cout << ans << endl;
  }
  return 0;
}
