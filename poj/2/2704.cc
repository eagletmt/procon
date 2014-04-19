#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  while (cin >> n && n != -1) {
    vector<string> board(n);
    for (int i = 0; i < n; i++) {
      cin >> board[i];
    }

    vector<vector<long long> > dp(n, vector<long long>(n, 0));
    dp[0][0] = 1;
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        for (int k = 0; k < j; k++) {
          if (k + board[i][k]-'0' == j) {
            dp[i][j] += dp[i][k];
          }
        }
        for (int k = 0; k < i; k++) {
          if (k + board[k][j]-'0' == i) {
            dp[i][j] += dp[k][j];
          }
        }
      }
    }
    cout << dp[n-1][n-1] << endl;
  }
  return 0;
}
