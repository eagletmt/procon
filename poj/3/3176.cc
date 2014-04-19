#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int N;
  cin >> N;
  vector<vector<int> > scores(N);
  for (int i = 0; i < N; i++) {
    scores[i].resize(i+1);
    for (int j = 0; j < i+1; j++) {
      cin >> scores[i][j];
    }
  }

  vector<vector<int> > dp(N, vector<int>(N+1, 0));
  dp[0][0] = scores[0][0];
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < i+1; j++) {
      if (j == 0) {
        dp[i][0] = dp[i-1][0] + scores[i][0];
      } else if (j == i) {
        dp[i][i] = dp[i-1][i-1] + scores[i][i];
      } else {
        dp[i][j] = max(dp[i-1][j], dp[i-1][j-1]) + scores[i][j];
      }
    }
  }
  int m = 0;
  for (int j = 0; j <= N; j++) {
    m = max(m, dp[N-1][j]);
  }
  cout << m << endl;
  return 0;
}
