#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int x, y;
    cin >> x >> y;
    vector<pair<int,int> > v;
    cin >> x >> y;
    v.push_back(make_pair(x, y));
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
      cin >> x >> y;
      v.push_back(make_pair(x, y));
    }
    ++N;

    vector<vector<int> > dp(1<<N, vector<int>(N, 1000000));
    for (int i = 0; i < N; i++) {
      dp[1<<i][i] = abs(v[i].first - v[0].first) + abs(v[i].second - v[0].second);
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
          dp[t][j] = min(dp[t][j], dp[s][i] + abs(v[j].first-v[i].first) + abs(v[j].second-v[i].second));
        }
      }
    }
    cout << "The shortest path has length " << dp[(1<<N)-1][0] << endl;
  }
  return 0;
}
