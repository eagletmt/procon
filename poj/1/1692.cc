#include <iostream>
#include <vector>
using namespace std;

int rindex(const vector<int>& v, int x, int n)
{
  for (int i = n-1; i >= 0; i--) {
    if (v[i] == x) {
      return i;
    }
  }
  return -1;
}

int solve(const vector<int>& v, const vector<int>& w)
{
  const int N1 = v.size(), N2 = w.size();
  vector<vector<int> > dp(N1, vector<int>(N2, 0));
  for (int i = 1; i < N1; i++) {
    for (int j = 1; j < N2; j++) {
      dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
      if (v[i] != w[j]) {
        int k = rindex(v, w[j], i);
        int l = rindex(w, v[i], j);
        if (k > 0 && l > 0) {
          dp[i][j] = max(dp[i][j], dp[k-1][l-1] + 2);
        } else if (k != -1 && l != -1) {
          dp[i][j] = max(dp[i][j], 2);
        }
      }
    }
  }
  return dp[N1-1][N2-1];
}

int main()
{
  int M;
  cin >> M;
  while (M-- > 0) {
    int N1, N2;
    cin >> N1 >> N2;
    vector<int> v(N1), w(N2);
    for (int i = 0; i < N1; i++) {
      cin >> v[i];
    }
    for (int i = 0; i < N2; i++) {
      cin >> w[i];
    }
    cout << solve(v, w) << endl;
  }
  return 0;
}