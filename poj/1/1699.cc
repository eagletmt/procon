#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int combine(const string& s, const string& t)
{
  for (string::size_type i = min(s.size(), t.size()); i > 0; i--) {
    if (s.substr(s.size()-i) == t.substr(0, i)) {
      return i;
    }
  }
  return 0;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    vector<string> v(N);
    int len = 0;
    for (int i = 0; i < N; i++) {
      cin >> v[i];
      len += v[i].size();
    }
    vector<vector<int> > comm(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i != j) {
          comm[i][j] = combine(v[i], v[j]);
        } else {
          comm[i][j] = 0;
        }
      }
    }

    vector<vector<int> > dp(1<<N, vector<int>(N, 1000000));
    for (int i = 0; i < N; i++) {
      dp[(1<<i)][i] = v[i].size();
    }
    for (int s = 0; s < (1<<N); s++) {
      for (int i = 0; i < N; i++) {
        if (!(s & (1<<i))) {
          continue;
        }
        for (int j = 0; j < N; j++) {
          if (s & (1<<j)) {
            continue;
          }
          const int t = s | (1<<j);
          dp[t][j] = min(dp[t][j], static_cast<int>(dp[s][i] + v[j].size() - comm[i][j]));
        }
      }
    }
    int ans = 1000000;
    for (int i = 0; i < N; i++) {
      ans = min(ans, dp[(1<<N)-1][i]);
    }
    cout << ans << endl;
  }
  return 0;
}