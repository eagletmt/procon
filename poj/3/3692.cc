#include <cstdio>
#include <vector>
using namespace std;

bool bm_augment(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (bm_augment(g, match_to[*it], match_to, visited)) {
        match_to[u] = *it;
        match_to[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

// O(V(V+E))
// Ford Fulkerson06EY09_62�0E
int bipartite_matching(const vector<vector<int> >& g, int L)  // {{{
{
  const int N = g.size();
  vector<int> match_to(N, -1);
  int match = 0;
  for (int u = 0; u < L; u++) {
    vector<bool> visited(N, false);
    if (bm_augment(g, u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int G, B, M;
  for (int Ti = 1; scanf("%d %d %d", &G, &B, &M) != EOF && G > 0; Ti++) {
    vector<vector<int> > m(G, vector<int>(B, true));
    for (int i = 0; i < M; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      --x;  --y;
      m[x][y] = false;
    }
    vector<vector<int> > g(G+B);
    for (int i = 0; i < G; i++) {
      for (int j = 0; j < B; j++) {
        if (m[i][j]) {
          g[i].push_back(j+G);
          g[j+G].push_back(i);
        }
      }
    }
    printf("Case %d: %d\n", Ti, G+B - bipartite_matching(g, G));
  }
  return 0;
}