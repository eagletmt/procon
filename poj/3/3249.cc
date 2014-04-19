#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) == 2) {
    static long long profits[100000];
    for (int i = 0; i < N; i++) {
      scanf("%lld", &profits[i]);
    }
    static vector<int> g[100000];
    for (int i = 0; i < N; i++) {
      g[i].clear();
    }
    static int in[100000];
    fill_n(in, N, 0);
    for (int i = 0; i < M; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      g[u].push_back(v);
      ++in[v];
    }

    static long long dp[100000];
    long long ans = -100000;
    queue<int> q;
    for (int i = 0; i < N; i++) {
      if (in[i] == 0) {
        // source
        dp[i] = profits[i];
        q.push(i);
      } else {
        dp[i] = -100000000LL;
      }
    }

    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      if (g[n].empty()) {
        ans = max(ans, dp[n]);
      } else {
        for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
          dp[*it] = max(dp[*it], dp[n] + profits[*it]);
          --in[*it];
          if (in[*it] == 0) {
            q.push(*it);
          }
        }
      }
    }

    printf("%lld\n", ans);
  }
  return 0;
}