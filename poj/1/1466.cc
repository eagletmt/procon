#include <cstdio>
#include <vector>
using namespace std;

bool augument(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (augument(g, match_to[*it], match_to, visited)) {
        //match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<vector<int> >& g)  // {{{
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
  return match;
} // }}}

int main()
{
  int n;
  while (scanf("%d", &n) != EOF) {
    vector<vector<int> > g(n);
    for (int i = 0; i < n; i++) {
      int u, m;
      scanf("%d", &u);
      getchar();  getchar();  getchar();
      scanf("%d", &m);
      getchar();
      for (int j = 0; j < m; j++) {
        int v;
        scanf("%d", &v);
        g[u].push_back(v);
      }
    }
    printf("%d\n", n - bipartite_matching(g)/2);
  }
  return 0;
}
