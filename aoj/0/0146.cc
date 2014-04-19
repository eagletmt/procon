#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct kura
{
  int id, dist, count;
};

int main()
{
  int N;
  cin >> N;
  vector<kura> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i].id >> v[i].dist >> v[i].count;
  }
  vector<vector<double> > dp(1<<N, vector<double>(N, 1e10));
  vector<vector<int> > prev(1<<N, vector<int>(N, -1));
  for (int i = 0; i < N; i++) {
    dp[1<<i][i] = 0.0;
  }
  for (unsigned s = 0; s < (1u<<N); s++) {
    for (int i = 0; i < N; i++) {
      if (!(s & (1<<i))) {
        continue;
      }
      for (int j = 0; j < N; j++) {
        if (s & (1<<j)) {
          continue;
        }
        int w = 0;
        for (int k = 0; k < N; k++) {
          if (s & (1<<k)) {
            w += v[k].count * 20;
          }
        }
        const double d = abs(v[i].dist - v[j].dist);
        const double vv = 2000.0/(70.0+w);
        const double t = dp[s][i] + d/vv;
        const unsigned u = s | (1<<j);
        double& next = dp[u][j];
        if (t < next) {
          next = t;
          prev[u][j] = i;
        }
      }
    }
  }
  int idx = min_element(dp[(1<<N)-1].begin(), dp[(1<<N)-1].end()) - dp[(1<<N)-1].begin();
  vector<int> ans;
  for (unsigned s = (1u<<N)-1; idx != -1;) {
    ans.push_back(v[idx].id);
    const unsigned t = s;
    s &= ~(1<<idx);
    idx = prev[t][idx];
  }
  for (vector<int>::const_reverse_iterator it = ans.rbegin(); it != ans.rend(); ++it) {
    if (it != ans.rbegin()) {
      cout << " ";
    }
    cout << *it;
  }
  cout << endl;
  return 0;
}
