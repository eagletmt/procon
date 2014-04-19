#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int T, W;
  cin >> T >> W;

  vector<bool> tree_1(T);
  for (int i = 0; i < T; i++) {
    int t;
    cin >> t;
    tree_1[i] = (t == 1);
  }

  vector<vector<pair<int,int> > > dp(T+1, vector<pair<int,int> >(W+1, make_pair(0, 0)));
  for (int i = 1; i <= T; i++) {
    for (int j = 0; j <= W; j++) {
      if (j == 0) {
        // no more move
        if (tree_1[i-1]) {
          dp[i][0].first = dp[i-1][0].first + 1;
          dp[i][0].second = dp[i-1][0].second;
        } else {
          dp[i][0].second = dp[i-1][0].second + 1;
          dp[i][0].first = dp[i-1][0].first;
        }
      } else {
        if (tree_1[i-1]) {
          dp[i][j].first = max(dp[i-1][j].first, dp[i-1][j-1].second) + 1;
          dp[i][j].second = dp[i-1][j].second;
        } else {
          dp[i][j].second = max(dp[i-1][j-1].first, dp[i-1][j].second) + 1;
          dp[i][j].first = dp[i-1][j].first;
        }
      }
    }
  }

  int m = 0;
  for (int i = 0; i <= W; i++) {
    m = max(m, max(dp[T][i].first, dp[T][i].second));
  }
  cout << m << endl;
  return 0;
}