#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int solve(const vector<int>& row)
{
  const int N = row.size();
  vector<vector<int> > dp(N, vector<int>(N, 0));

  for (int d = 1; d < N; d++) {
    for (int i = 1; i+d < N; i++) {
      const int j = i+d;
      int m = numeric_limits<int>::max();
      for (int k = i; k < j; k++) {
        m = min(m, dp[i][k] + dp[k+1][j] + row[i-1]*row[k]*row[j]);
      }
      dp[i][j] = m;
    }
  }
  return dp[1][N-1];
}

int main(void)
{
  int N;
  cin >> N;
  vector<int> row(N);
  for (int i = 0; i < N; i++) {
    cin >> row[i];
  }
  cout << solve(row) << endl;
  return 0;
}
