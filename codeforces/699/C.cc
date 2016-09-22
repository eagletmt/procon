#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  vector<int> xs(N);
  for (int i = 0; i < N; i++) {
    cin >> xs[i];
  }

  static const int INF = 100000000;
  vector<vector<int>> dp(N + 1, vector<int>(3, INF));
  dp[0][0] = dp[0][1] = dp[0][2] = 0;
  for (int i = 0; i < N; i++) {
    dp[i + 1][0] = min(dp[i][0], min(dp[i][1], dp[i][2])) + 1;
    if (xs[i] & 1) {
      dp[i + 1][1] = min(dp[i][0], dp[i][2]);
    }
    if (xs[i] & 2) {
      dp[i + 1][2] = min(dp[i][0], dp[i][1]);
    }
  }
  cout << min(dp[N][0], min(dp[N][1], dp[N][2])) << endl;
  return 0;
}
