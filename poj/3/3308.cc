#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
#include <cmath>
using namespace std;

template <typename T>
T edmonds_karp(int N, const vector<vector<T> >& capacity, int source, int sink)/*{{{*/
{
  vector<vector<T> > flow(N, vector<T>(N, 0));
  T max_flow = 0;

  while (true) {
    vector<int> parent(N, -1);
    queue<int> q;
    q.push(source);

    while (!q.empty() && parent[sink] < 0) {
      const int v = q.front();
      q.pop();

      for (int u = 0; u < N; u++) {
        if (parent[u] < 0 && capacity[v][u] - flow[v][u] > 0) {
          parent[u] = v;
          if (u == sink) {
            break;
          }
          q.push(u);
        }
      }
    }

    if (parent[sink] < 0) {
      break;
    }

    T aug = numeric_limits<T>::max();
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      aug = min(aug, capacity[u][v] - flow[u][v]);
    }
    max_flow += aug;
    for (int v = sink; v != source; v = parent[v]) {
      const int u = parent[v];
      flow[u][v] += aug;
      flow[v][u] -= aug;
    }
  }

  return max_flow;
}/*}}}*/

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, M, L;
    cin >> N >> M >> L;
    vector<vector<long double> > g(N+M+2, vector<long double>(N+M+2, 0));
    for (int i = 0; i < N; i++) {
      long double r;
      cin >> r;
      g[0][i+1] = log(r);
    }
    for (int i = 0; i < M; i++) {
      long double c;
      cin >> c;
      g[i+N+1][N+M+1] = log(c);
    }
    for (int i = 0; i < L; i++) {
      int r, c;
      cin >> r >> c;
      g[r][c+N] = 10000;
    }

    printf("%.4Lf\n", exp(edmonds_karp(N+M+2, g, 0, N+M+1)));
  }
  return 0;
}