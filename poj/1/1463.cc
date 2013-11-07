#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

static const int MAXN = 1500;
vector<int> g[MAXN];
bool visited[MAXN];

pair<int,int> dfs(int n)
{
  pair<int,int> r(0, 1);
  visited[n] = true;
  for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
    if (!visited[*it]) {
      const pair<int,int> p = dfs(*it);
      r.first += p.second;
      r.second += min(p.first, p.second);
    }
  }
  return r;
}

int main()
{
  int N;
  while (scanf("%d", &N) != EOF) {
    for (int i = 0; i < N; i++) {
      g[i].clear();
    }

    for (int i = 0; i < N; i++) {
      int from, M;
      scanf("%d:(%d)", &from, &M);
      for (int j = 0; j < M; j++) {
        int to;
        scanf("%d", &to);
        g[from].push_back(to);
        g[to].push_back(from);
      }
    }

    fill_n(visited, N, false);
    const pair<int,int> r = dfs(0);
    printf("%d\n", min(r.first, r.second));
  }
  return 0;
}
