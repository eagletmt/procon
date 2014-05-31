#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int calc(const vector<vector<string> >& subs, const vector<vector<int> >& servers)
{
  const int N = servers.size();
  int c = 0;

  for (int i = 0; i < N; i++) {
    const int L = servers[i].size();
    if (L == 0) {
      // invalid
      return -1;
    }
    vector<string> v;
    for (int j = 0; j < L; j++) {
      const vector<string>& t = subs[servers[i][j]];
      const int K = t.size();
      for (int k = 0; k < K; k++) {
        v.push_back(t[k]);
      }
    }
    sort(v.begin(), v.end());
    v.erase(unique(v.begin(), v.end()), v.end());
    c += v.size() + 1;
  }

  return c;
}

int ans, counts;

void solve(const vector<vector<string> >& subs, int idx, vector<vector<int> >& servers)
{
  const int N = servers.size();
  const int M = subs.size();
  if (idx == M) {
    const int c = calc(subs, servers);
    if (c > ans) {
      ans = c;
      counts = 1;
    } else if (ans == c) {
      ++counts;
    }
    return;
  }

  for (int i = 0; i < N; i++) {
    servers[i].push_back(idx);
    solve(subs, idx+1, servers);
    servers[i].pop_back();
  }
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N, M;
    cin >> M >> N;
    vector<string> v(M);
    vector<vector<string> > substrings(M);
    for (int i = 0; i < M; i++) {
      cin >> v[i];
      const int L = v[i].size();
      for (int j = 0; j < L; j++) {
        substrings[i].push_back(v[i].substr(0, j+1));
      }
    }

    ans = -1;
    counts = 0;
    vector<vector<int> > servers(N);
    solve(substrings, 0, servers);
    cout << ans << " " << counts << endl;
  }
  return 0;
}
