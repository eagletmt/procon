#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int dfs(const vector<vector<int> >& g, vector<int>& marbles, int n)
{
  if (g[n].empty()) {
    return 0;
  } else {
    int ans = 0;
    for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
      ans += dfs(g, marbles, *it);
      if (marbles[*it] > 1) {
        marbles[n] += marbles[*it] - 1;
        ans += marbles[*it] - 1;
        marbles[*it] = 1;
      } else if (marbles[*it] < 1) {
        marbles[n] -= 1 - marbles[*it];
        ans += 1 - marbles[*it];
        marbles[*it] = 1;
      }
    }
    return ans;
  }
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<vector<int> > g(N);
    vector<int> marbles(N);
    vector<int> deg(N, 0);
    for (int i = 0; i < N; i++) {
      int v, d, n;
      scanf("%d %d %d", &v, &d, &n);
      --v;
      marbles[v] = d;
      for (int j = 0; j < n; j++) {
        int u;
        scanf("%d", &u);
        --u;
        g[v].push_back(u);
        ++deg[u];
      }
    }

    for (int i = 0; i < N; i++) {
      if (deg[i] == 0) {
        int ans = dfs(g, marbles, i);
        printf("%d\n", ans);
        break;
      }
    }
  }
  return 0;
}