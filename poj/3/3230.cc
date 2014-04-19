#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
  int m, n;
  while (cin >> n >> m && m + n != 0) {
    vector<vector<int> > expense(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> expense[i][j];
      }
    }

    vector<vector<int> > income(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cin >> income[i][j];
      }
    }

    vector<vector<int> > dp(m, vector<int>(n, numeric_limits<int>::min()));
    for (int i = 0; i < n; i++) {
      dp[0][i] = income[0][i] - expense[0][i];
    }
    for (int i = 1; i < m; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < n; k++) {
          dp[i][j] = max(dp[i][j], dp[i-1][k] - expense[k][j] + income[i][j]);
        }
      }
    }
    int r = numeric_limits<int>::min();
    for (int i = 0; i < n; i++) {
      r = max(r, dp[m-1][i]);
    }
    cout << r << endl;
  }
  return 0;
}
