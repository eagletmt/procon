#include <cstdio>
#include <vector>
#include <queue>
using namespace std;
static const double EPS = 1e-6;

struct road
{
  int node, len, limit;
  road() {}
  road(int x, int d, int c) : node(x), len(d), limit(c) {}
};

struct state
{
  int p, n, v;
  double c;
  state(int prev, int node, int velocity, double cost) : p(prev), n(node), v(velocity), c(cost) {}
  bool operator<(const state& that) const { return c > that.c; }
};

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    int S, G;
    scanf("%d %d", &S, &G);
    --S;  --G;
    vector<vector<road> > g(N);
    for (int i = 0; i < M; i++) {
      int x, y, d, c;
      scanf("%d %d %d %d", &x, &y, &d, &c);
      --x;  --y;
      g[x].push_back(road(y, d, c));
      g[y].push_back(road(x, d, c));
    }
    vector<vector<vector<double> > > dist(N, vector<vector<double> >(N, vector<double>(31, 1e7)));
    dist[S][S][0] = 0.0;
    priority_queue<state> q;
    q.push(state(S, S, 0, 0.0));
    double ans = 1e7;
    while (!q.empty()) {
      const int prev = q.top().p;
      const int n = q.top().n;
      const int v = q.top().v;
      const double cost = q.top().c;
      q.pop();
      if (n == G && v == 1) {
        ans = min(ans, cost);
        continue;
      }
      for (vector<road>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (it->node == prev) {
          continue;
        }
        for (int d = -1; d <= 1; d++) {
          if (v+d >= 1 && v+d <= it->limit) {
            const double c = cost + double(it->len) / (v+d);
            if (dist[prev][it->node][v+d] - c > EPS) {
              dist[prev][it->node][v+d] = c;
              q.push(state(n, it->node, v+d, c));
            }
          }
        }
      }
    }
    if (ans >= 1e7) {
      puts("unreachable");
    } else {
      printf("%.4f\n", ans);
    }
  }
  return 0;
}
