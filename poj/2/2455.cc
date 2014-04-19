#include <cstdio>
#include <vector>
#include <queue>
#include <limits>
using namespace std;
static const int M = 200;
static const int INF = 1000000;

template <class T>
T dinic_augment(const T capacity[M][M], int N, T flow[M][M], int level[M], bool finished[M], int u, int sink, T cur)/*{{{*/
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
T dinic(const T capacity[M][M], int N, int source, int sink)/*{{{*/
{
  static T flow[M][M];
  for (int i = 0; i < N; i++) {
    fill_n(flow[i], N, 0);
  }
  T max_flow = 0;

  while (true) {
    static int level[M];
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

    static bool finished[M];
    fill_n(finished, M, false);
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
  int N, P, T;
  scanf("%d %d %d", &N, &P, &T);
  static vector<pair<int,int> > g[M];
  for (int i = 0; i < P; i++) {
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    --a;  --b;
    g[a].push_back(make_pair(b, c));
    g[b].push_back(make_pair(a, c));
  }

  int left = 0, right = 1000000;
  while (left < right) {
    const int mid = (left + right)/2;
    static int capacity[M][M];
    for (int i = 0; i < N; i++) {
      fill_n(capacity[i], N, 0);
    }
    for (int i = 0; i < N; i++) {
      for (vector<pair<int,int> >::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
        if (it->second <= mid) {
          ++capacity[i][it->first];
        }
      }
    }
    const int f = dinic(capacity, N, 0, N-1);
    if (f >= T) {
      right = mid;
    } else {
      left = mid+1;
    }
  }
  printf("%d\n", left);
  return 0;
}