#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct edge
{
  int a, b, c, p, r;
};

struct state
{
  int n, s, c;
  state(int x, int y, int z) : n(x), s(y), c(z) {}
  bool operator<(const state& t) const { return c > t.c; }
};

int main()
{
  int N, M;
  cin >> N >> M;
  vector<vector<edge> > g(N);
  for (int i = 0; i < M; i++) {
    edge e;
    cin >> e.a >> e.b >> e.c >> e.p >> e.r;
    --e.a;  --e.b;  --e.c;
    g[e.a].push_back(e);
  }

  static const int INF = 10000000;
  vector<vector<int> > dist(N, vector<int>(1<<N, INF));
  dist[0][1<<0] = 0;
  priority_queue<state> q;
  q.push(state(0, 1<<0, 0));
  while (!q.empty()) {
    const state s = q.top();
    q.pop();
    if (s.n == N-1) {
      cout << s.c << endl;
      return 0;
    }
    if (dist[s.n][s.s] < s.c) {
      continue;
    }
    for (vector<edge>::const_iterator it = g[s.n].begin(); it != g[s.n].end(); ++it) {
      const int v = it->b;
      if (s.s & (1<<it->c)) {
        const int d = dist[s.n][s.s] + it->p;
        const int t = s.s | (1<<v);
        if (d < dist[v][t]) {
          dist[v][t] = d;
          q.push(state(v, t, d));
        }
      }
      const int d = dist[s.n][s.s] + it->r;
      const int t = s.s | (1<<v);
      if (d < dist[v][t]) {
        dist[v][t] = d;
        q.push(state(v, t, d));
      }
    }
  }
  cout << "impossible" << endl;
  return 0;
}