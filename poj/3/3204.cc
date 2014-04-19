#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
static const int MAXN = 500;
static const int INF = 10000000;

template <class T>
T dinic_augment(const T capacity[MAXN][MAXN], int N, T flow[MAXN][MAXN], int level[MAXN], bool finished[MAXN], int u, int sink, T cur)/*{{{*/
{
  if (u == sink || cur == 0) {
    return cur;
  }
  if (finished[u]) {
    return 0;
  }
  finished[u] = true;
  for (int v = 0; v < N; v++) {
    if (capacity[u][v] - flow[u][v] > 0 && level[v] > level[u]) {
      const T f = dinic_augment(capacity, N, flow, level, finished, v, sink, min(cur, capacity[u][v] - flow[u][v]));
      if (f > 0) {
        flow[u][v] += f;
        flow[v][u] -= f;
        finished[u] = false;
        return f;
      }
    }
  }
  return 0;
}/*}}}*/
template <typename T>
T dinic(const T capacity[MAXN][MAXN], T flow[MAXN][MAXN], int N, int source, int sink)/*{{{*/
{
  T max_flow = 0;

  while (true) {
    static int level[MAXN];
    fill_n(level, N, -1);
    level[source] = 0;
    queue<int> q;
    q.push(source);

    int d = N;
    while (!q.empty() && level[q.front()] < d) {
      const int u = q.front();
      q.pop();

      if (u == sink) {
        d = level[u];
      }
      for (int v = 0; v < N; v++) {
        if (level[v] < 0 && capacity[u][v] - flow[u][v] > 0) {
          q.push(v);
          level[v] = level[u] + 1;
        }
      }
    }

    static bool finished[MAXN];
    fill_n(finished, MAXN, false);
    bool updated = false;
    while (true) {
      const T f = dinic_augment(capacity, N, flow, level, finished, source, sink, INF);
      if (f == 0) {
        break;
      }
      max_flow += f;
      updated = true;
    }

    if (!updated) {
      break;
    }
  }

  return max_flow;
}/*}}}*/

int main()
{
  int N, M;
  scanf("%d%d", &N, &M);
  static int capacity[MAXN][MAXN];
  for (int i = 0; i < M; i++) {
    int a, b, c;
    scanf("%d%d%d", &a, &b, &c);
    capacity[a][b] = c;
  }
  static int flow[MAXN][MAXN];
  dinic(capacity, flow, N, 0, N-1);
  vector<int> mark(N, 0);
  // source -> sink
  {
    queue<int> q;
    q.push(0);
    mark[0] |= 1;
    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      for (int i = 0; i < N; i++) {
        if (capacity[n][i] != 0 && flow[n][i] < capacity[n][i] && !(mark[i] & 1)) {
          mark[i] |= 1;
          q.push(i);
        }
      }
    }
  }
  // sink -> source
  int ans = 0;
  {
    queue<int> q;
    q.push(N-1);
    mark[N-1] |= 2;
    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      for (int i = 0; i < N; i++) {
        if (capacity[i][n] != 0 && flow[i][n] < capacity[i][n] && !(mark[i] & 2)) {
          mark[i] |= 2;
          q.push(i);
        } else if (capacity[i][n] != 0 && flow[i][n] == capacity[i][n] && (mark[i] & 1)) {
          ++ans;
        }
      }
    }
  }
  printf("%d\n", ans);
  return 0;
}