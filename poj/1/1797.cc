#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, M;
    scanf("%d %d", &N, &M);
    static vector<pair<int,int> > g[1000];
    for (int i = 0; i < N; i++) {
      g[i].clear();
    }
    for (int i = 0; i < M; i++) {
      int a, b, w;
      scanf("%d %d %d", &a, &b, &w);
      --a;  --b;
      g[a].push_back(make_pair(b, w));
      g[b].push_back(make_pair(a, w));
    }
    priority_queue<pair<int,int> > q;
    q.push(make_pair(10000000, 0));
    static int dists[1000];
    fill_n(dists, N, 0);
    dists[0] = 10000000;
    while (!q.empty()) {
      const int n = q.top().second;
      const int d = q.top().first;
      q.pop();
      if (n == N-1) {
        printf("Scenario #%d:\n%d\n\n", Ti, d);
        break;
      }
      for (vector<pair<int,int> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        const int c = min(d, it->second);
        if (c > dists[it->first]) {
          dists[it->first] = c;
          q.push(make_pair(c, it->first));
        }
      }
    }
  }
  return 0;
}