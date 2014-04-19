#include <iostream>
#include <vector>
using namespace std;

bool augument(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited)
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (augument(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
}

int bipartite_matching(const vector<vector<int> >& g, int L, vector<pair<int,int> >& matching)
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    vector<bool> visited(N, false);
    if (augument(g, u, match_to, visited)) {
      match++;
    }
  }
  for (int u = 0; u < L; u++) {
    if (match_to[u] >= 0) {
      matching.push_back(make_pair(u, match_to[u]));
    }
  }
  return match;
}

int gcd(int a, int b)
{
  if (a < b) {
    swap(a, b);
  }
  int r;
  while ((r = a % b) != 0) {
    a = b;
    b = r;
  }
  return b;
}

int main()
{
  int n, m;
  while (cin >> m >> n && !(m == 0 && n == 0)) {
    vector<int> blue(m), red(n);
    for (int i = 0; i < m; i++) {
      cin >> blue[i];
    }
    for (int i = 0; i < n; i++) {
      cin >> red[i];
    }

    vector<vector<int> > g(n+m);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (gcd(blue[i], red[j]) > 1) {
          g[i].push_back(m+j);
        }
      }
    }

    vector<pair<int,int> > matching;
    int ans = bipartite_matching(g, m, matching);
    cout << ans << endl;
  }
  return 0;
}
