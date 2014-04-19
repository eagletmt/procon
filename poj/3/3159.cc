#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;
struct edge
{
  int a, b, c;
  bool operator<(const edge& that) const
  {
    if (a == that.a) {
      return c < that.c;
    } else {
      return a < that.a;
    }
  }
};

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static edge edges[150000];
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &edges[i].a, &edges[i].b, &edges[i].c);
    --edges[i].a;
    --edges[i].b;
  }
  sort(edges, edges+M);
  static int begins[30000];
  begins[0] = 0;
  for (int i = 1; i < M; i++) {
    if (edges[i].a != edges[i-1].a) {
      begins[edges[i].a] = i;
    }
  }

  static int dist[30000];
  fill_n(dist, N, 10000000);
  priority_queue<pair<int,int> > q;
  q.push(make_pair(0, 0));
  dist[0] = 0;
  while (!q.empty()) {
    const int c = -q.top().first;
    const int n = q.top().second;
    q.pop();
    if (n == N-1) {
      printf("%d\n", c);
      break;
    }
    if (dist[n] < c) {
      continue;
    }
    for (int i = begins[n]; i < M && edges[i].a == n; i++) {
      const int cc = c + edges[i].c;
      if (cc < dist[edges[i].b]) {
        dist[edges[i].b] = cc;
        q.push(make_pair(-cc, edges[i].b));
      }
    }
  }
  return 0;
}