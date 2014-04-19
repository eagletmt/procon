#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

template <typename T>
T dfs(vector<vector<T> >& capacity, int u, int sink, const vector<int>& level, T cur_max = numeric_limits<T>::max())
{
  if (u == sink) {
    return cur_max;
  } else {
    const int N = capacity.size();
    for (int v = 0; v < N; v++) {
      if (capacity[u][v] > 0 && level[v] == level[u]+1) {
        T f = dfs(capacity, v, sink, level, min(cur_max, capacity[u][v]));
        if (f != 0) {
          capacity[u][v] -= f;
          capacity[v][u] += f;
          return f;
        }
      }
    }
    return 0;
  }
}

template <typename T>
T dinic(vector<vector<T> > capacity, int source, int sink)
{
  const int N = capacity.size();

  T max_flow = 0;

  while (true) {
    vector<int> level(N, -1);
    queue<int> q;
    q.push(source);
    level[source] = 0;

    while (!q.empty() && level[sink] == -1) {
      const int u = q.front();
      q.pop();
      for (int v = 0; v < N; v++) {
        if (level[v] == -1 && capacity[u][v] > 0) {
          q.push(v);
          level[v] = level[u] + 1;
        }
      }
    }

    if (level[sink] == -1) {
      break;
    }

    for (T flow = 1; flow > 0; max_flow += flow) {
      flow = dfs(capacity, source, sink, level);
    }
  }
  return max_flow;
}

int main()
{
  int n, np, nc, m;
  while (cin >> n >> np >> nc >> m) {
    vector<vector<int> > cap(n+2, vector<int>(n+2, 0));

    for (int i = 0; i < m; i++) {
      char c;
      int u, v, z;
      cin >> c >> u >> c >> v >> c >> z;
      cap[u][v] = z;
    }
    for (int i = 0; i < np; i++) {
      char c;
      int u, z;
      cin >> c >> u >> c >> z;
      cap[n][u] = z;
    }
    for (int i = 0; i < nc; i++) {
      char c;
      int u, z;
      cin >> c >> u >> c >> z;
      cap[u][n+1] = z;
    }
    cout << dinic(cap, n, n+1) << endl;
  }
  return 0;
}
