#include <cstdio>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int g[501][501];

int stoer_wagner(int N)
{
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    v[i] = i;
  }

  int cut = numeric_limits<int>::max();
  for (int m = N; m > 1; m--) {
    //vector<int> ws(m, 0);
    int ws[501];
    fill(ws, ws + m, 0);
    int s, t = 0;
    int w;
    for (int k = 0; k < m; k++) {
      s = t;
      t = distance(ws, max_element(ws, ws + m));
      w = ws[t];
      ws[t] = -1;
      for (int i = 0; i < m; i++) {
        if (ws[i] >= 0) {
          ws[i] += g[v[t]][v[i]];
        }
      }
    }
    for (int i = 0; i < m; i++) {
      g[v[i]][v[s]] += g[v[i]][v[t]];
      g[v[s]][v[i]] += g[v[t]][v[i]];
    }
    v.erase(v.begin() + t);
    cut = min(cut, w);
  }
  return cut;
}

int main()
{
  int N, M;
  while (scanf("%d %d", &N, &M) != EOF) {
    for (int i = 0; i < N; i++) {
      fill(g[i], g[i] + N, 0);
    }
    for (int i = 0; i < M; i++) {
      int u, v, w;
      scanf("%d %d %d", &u, &v, &w);
      g[u][v] += w;
      g[v][u] += w;
    }
    printf("%d\n", stoer_wagner(N));
  }
  return 0;
}