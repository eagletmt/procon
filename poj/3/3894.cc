#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct edge
{
  int u, v;
  bool operator<(const edge& e) const { return u < e.u; }
};
static const int MAXV = 20000;
edge edges[1000000];
int begins[MAXV+1];

bool bm_augment( int u, int *match_to, int *visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (int i = begins[u]; i < begins[u+1]; i++) {
    const int v = edges[i].v;
    if (!visited[v]) {
      visited[v] = true;
      if (bm_augment(match_to[v], match_to, visited)) {
        match_to[u] = v;
        match_to[v] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

// O(V(V+E))
// Ford Fulkerson06EY09_62�0E
int bipartite_matching(int V, int L)  // {{{
{
  static int match_to[MAXV];
  fill_n(match_to, V, -1);
  int match = 0;
  for (int u = 0; u < L; u++) {
    static int visited[MAXV];
    fill_n(visited, V, 0);
    if (bm_augment(u, match_to, visited)) {
      match++;
    }
  }
  return match;
} // }}}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    const int V = 2*N;
    int E = 0;
    for (int i = 0; i < N; i++) {
      int job, S;
      scanf("%d: (%d)", &job, &S);
      for (int j = 0; j < S; j++) {
        int s;
        scanf("%d", &s);
        edges[E].u = job;
        edges[E].v = s;
        ++E;
        edges[E].u = s;
        edges[E].v = job;
        ++E;
      }
    }

    sort(edges, edges+E);
    fill_n(begins, MAXV+1, -1);
    begins[edges[0].u] = 0;
    for (int i = 1; i < E; i++) {
      if (edges[i].u != edges[i-1].u) {
        begins[edges[i].u] = i;
      }
    }
    begins[V] = E;
    for (int i = V-1; i > 0; i--) {
      if (begins[i] == -1) {
        begins[i] = begins[i+1];
      }
    }

    printf("%d\n", bipartite_matching(V, N));
  }
  return 0;
}