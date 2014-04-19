#include <iostream>
#include <vector>
using namespace std;

string strmax(const string& lhs, const string& rhs)
{
  const string::size_type l = lhs.size();
  const string::size_type r = rhs.size();
  if (l == r) {
    if (lhs.compare(rhs) < 0) {
      return rhs;
    } else {
      return lhs;
    }
  } else {
    if (l < r) {
      return rhs;
    } else {
      return lhs;
    }
  }
}

int main(void)
{
  int R, C;
  while (cin >> C >> R && C != 0) {
    vector<string> board(R);
    for (int i = 0; i < R; i++) {
      cin >> board[i];
    }

    vector<vector<string> > dp(R, vector<string>(C, ""));
    string secret = "";
    for (int i = 0; i < R; i++) {
      for (int j = 0; j < C; j++) {
        if (!isdigit(board[i][j])) {
          continue;
        }

        if (i == 0 && j == 0) {
          dp[i][j] = string(1, board[i][j]);
        } else if (i == 0) {
          dp[i][j] =  dp[i][j-1] + board[i][j];
        } else if (j == 0) {
          dp[i][j] =  dp[i-1][j] + board[i][j];
        } else {
          const string t = strmax(dp[i][j-1], dp[i-1][j]);
          dp[i][j] =  t + board[i][j];
        }
        if (dp[i][j][0] == '0') {
          dp[i][j] = dp[i][j].substr(1);
        }
        secret = strmax(secret, dp[i][j]);
      }
    }
    cout << secret << endl;
  }
  return 0;
}
