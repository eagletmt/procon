#include <cstdio>
#include <vector>
using namespace std;

inline long long abs(long long x)
{
  return x >= 0 ? x : -x;
}

long long dfs(const vector<int> *g, int u, bool *visited, long long *cnt)/*{{{*/
{
  visited[u] = true;
  for (vector<int>::const_iterator it = g[u].begin(); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      cnt[u] += dfs(g, *it, visited, cnt);
    }
  }
  return cnt[u];
}/*}}}*/

int main()
{
  int N, M;
  int Ti = 0;
  while (scanf("%d %d", &N, &M) != EOF && N != 0) {
    static long long cnt[100000];
    for (int i = 0; i < N; i++) {
      scanf("%lld", &cnt[i]);
    }
    static vector<int> g[100000];
    for (int i = 0; i < N; i++) {
      g[i].clear();
    }
    for (int i = 0; i < M; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      g[u].push_back(v);
      g[v].push_back(u);
    }

    static bool visited[100000];
    fill_n(visited, N, false);
    dfs(g, 0, visited, cnt);
    long long ans = 1LL<<50;
    for (int i = 1; i < N; i++) {
      ans = min(ans, abs(cnt[0] - 2*cnt[i]));
    }
    printf("Case %d: %lld\n", ++Ti, ans);
  }
  return 0;
}