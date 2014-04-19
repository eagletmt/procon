#include <iostream>
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
  int N, K;
  cin >> N >> K;
  vector<vector<int> > g(N+N);
  for (int i = 0; i < K; i++) {
    int r, c;
    cin >> r >> c;
    --r;  --c;
    g[r].push_back(c+N);
  }
  cout << bipartite_matching(g) << endl;
  return 0;
}
