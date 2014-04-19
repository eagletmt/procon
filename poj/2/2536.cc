#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;

bool augument(const vector<vector<int> >& g, int u, vector<int>& match_to, vector<bool>& visited) // {{{
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
} // }}}

int bipartite_matching(const vector<vector<int> >& g) // {{{
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
  int N, M, S, V;
  while (scanf("%d %d %d %d", &N, &M, &S, &V) == 4) {
    vector<P> gophers, holes;
    gophers.reserve(N);
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      gophers.push_back(P(x, y));
    }
    holes.reserve(M);
    for (int i = 0; i < M; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);
      holes.push_back(P(x, y));
    }
    const double R = S*V;

    vector<vector<int> > g(N+M);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        if (abs(gophers[i] - holes[j]) < R) {
          g[i].push_back(j+N);
        }
      }
    }
    printf("%d\n", N - bipartite_matching(g));
  }
  return 0;
}