#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
  static char pat[1001], passwd[10001];
  while (scanf("%s %s", pat, passwd) != EOF) {
    const int pat_len = strlen(pat);
    const int passwd_len = strlen(passwd);

    static int dp[1001][10001];
    static const int INF = 10000000;
    for (int i = 0; i <= pat_len; i++) {
      dp[i][passwd_len] = INF;
    }
    for (int j = 0; j <= passwd_len; j++) {
      dp[pat_len][j] = 0;
    }

    for (int i = pat_len-1; i >= 0; i--) {
      for (int j = passwd_len; j >= 0; j--) {
        const int cost = passwd[j] - 'a' + 1;
        if (passwd[j] == pat[i] || pat[i] == '?') {
          if (j+1 <= passwd_len) {
            dp[i][j] = dp[i+1][j+1] + cost;
          }
        } else if (pat[i] == '*') {
          dp[i][j] = dp[i+1][j];
          if (j+1 <= passwd_len) {
            dp[i][j] = min(dp[i][j], dp[i][j+1] + cost);
          }
        } else {
          dp[i][j] = INF;
        }
        dp[i][j] = min(dp[i][j], INF);
      }
    }
    int ans = INF;
    for (int j = 0; j <= passwd_len; j++) {
      ans = min(ans, dp[0][j]);
    }
    printf("%d\n", ans == INF ? -1 : ans);
  }
  return 0;
}