#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N, M, V;
  scanf("%d%d%d", &N, &M, &V);
  static int xs[50002], ys[50002];
  for (int i = 0; i < N; i++) {
    scanf("%d%d", &xs[i+1], &ys[i+1]);
  }
  static vector<pair<int,int> > g[50000];
  for (int i = 0; i < M; i++) {
    int a, b, t;
    scanf("%d%d%d", &a, &b, &t);
    g[a].push_back(make_pair(b, t));
    g[b].push_back(make_pair(a, t));
  }
  scanf("%d%d%d%d", &xs[0], &ys[0], &xs[N+1], &ys[N+1]);

  priority_queue<pair<long long,int> > q;
  q.push(make_pair(0LL, 0));
  static long long dist[50002];
  fill_n(dist, N+2, 1LL<<45);
  dist[0] = 0;
  while (!q.empty()) {
    const long long cost = -q.top().first;
    const int n = q.top().second;
    const long long dx1 = xs[n] - xs[0], dy1 = ys[n] - ys[0];
    const long long d1 = dx1*dx1 + dy1*dy1;
    q.pop();
    if (n == N+1) {
      printf("%lld\n", cost);
      goto FINISH;
    }
    for (vector<pair<int,int> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
      const int m = it->first;
      const long long c = cost + it->second;
      const long long dx2 = xs[m] - xs[0], dy2 = ys[m] - ys[0];
      const long long d2 = dx2*dx2 + dy2*dy2;
      if (c < dist[m] && (m == N+1 || (d1 < d2 && static_cast<long long>(V)*V*c*c < d2))) {
        dist[m] = c;
        q.push(make_pair(-c, m));
      }
    }
  }
  puts("Impossible");
FINISH:
  return 0;
}