#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
using namespace std;

int main()
{
  int n;
  while (scanf("%d", &n) == 1 && n != 0) {
    int m;
    scanf("%d", &m);
    vector<vector<pair<int,long double> > > g(n);
    for (int i = 0; i < m; i++) {
      int a, b, p;
      scanf("%d %d %d", &a, &b, &p);
      --a;  --b;
      g[a].push_back(make_pair(b, log(p * 0.01L)));
      g[b].push_back(make_pair(a, log(p * 0.01L)));
    }

    // dijkstra
    priority_queue<pair<long double, int> > q;
    q.push(make_pair(log(1.0L), 0));
    vector<long double> tbl(n, -numeric_limits<long double>::max());
    tbl[0] = log(1.0);
    while (!q.empty()) {
      const pair<long double, int> p = q.top();
      q.pop();
      if (p.second == n-1) {
        printf("%.6Lf percent\n", 100*exp(p.first));
        break;
      }
      for (vector<pair<int, long double> >::const_iterator it(g[p.second].begin()); it != g[p.second].end(); ++it) {
        const long double c = p.first + it->second;
        if (c > tbl[it->first]) {
          tbl[it->first] = c;
          q.push(make_pair(c, it->first));
        }
      }
    }
  }
  return 0;
}