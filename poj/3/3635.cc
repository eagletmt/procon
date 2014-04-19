#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct state
{
  int cost;
  int fuel;
  int node;
  state(int c, int f, int n) : cost(c), fuel(f), node(n) {}
  bool operator<(const state& that) const
  {
    return cost > that.cost;
  }
};

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static int price[1000];
  for (int i = 0; i < N; i++) {
    scanf("%d", &price[i]);
  }
  static vector<pair<int,int> > g[1000];
  for (int i = 0; i < M; i++) {
    int u, v, d;
    scanf("%d %d %d", &u, &v, &d);
    g[u].push_back(make_pair(v, d));
    g[v].push_back(make_pair(u, d));
  }
  int Q;
  scanf("%d", &Q);
  while (Q-- > 0) {
    int C, s, e;
    scanf("%d %d %d", &C, &s, &e);
    static int dist[1000][101];
    for (int i = 0; i < N; i++) {
      fill_n(dist[i], C+1, 1000000);
    }
    dist[s][0] = 0;
    priority_queue<state> q;
    q.push(state(0, 0, s));
    while (!q.empty()) {
      const int n = q.top().node;
      const int cost = q.top().cost;
      const int fuel = q.top().fuel;
      q.pop();
      if (n == e) {
        printf("%d\n", cost);
        goto NEXT;
      }
      for (vector<pair<int,int> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (fuel < C) {
          const int c = cost + price[n];
          if (c < dist[n][fuel+1]) {
            dist[n][fuel+1] = c;
            q.push(state(c, fuel+1, n));
          }
        }
        const int m = it->first;
        const int len = it->second;
        if (len <= fuel && cost < dist[m][fuel-len]) {
          dist[m][fuel-len] = cost;
          q.push(state(cost, fuel-len, m));
        }
      }
    }
    puts("impossible");
NEXT:
    ;
  }
  return 0;
}