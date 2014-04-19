#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <algorithm>
#include <iterator>
using namespace std;

struct edge/*{{{*/
{
  int to;
  int capacity;
  int cost;
  edge(int i, int c, int d) : to(i), capacity(c), cost(d) {}
};/*}}}*/

pair<int,vector<vector<int> > > primal_dual(const vector<vector<edge> >& g, int source, int sink)/*{{{*/
{
  const int N = g.size();
  vector<vector<int> > capacity(N, vector<int>(N, 0)), cost(N, vector<int>(N, 0)), flow(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (vector<edge>::const_iterator it = g[i].begin(); it != g[i].end(); ++it) {
      capacity[i][it->to] += it->capacity;
      cost[i][it->to] += it->cost;
    }
  }
  pair<int,int> total;  // (cost, flow)
  vector<int> h(N, 0);
  static const int INF = 10000000;
  for (int f = INF; f > 0; ) {
    vector<int> dist(N, INF);
    dist[source] = 0;
    vector<int> parent(N, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const int c = -q.top().first;
      q.pop();
      for (vector<edge>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
        if (capacity[n][it->to] - flow[n][it->to] > 0) {
          const int c2 = c + cost[n][it->to] + h[n] - h[it->to];
          if (c2 < dist[it->to]) {
            dist[it->to] = c2;
            parent[it->to] = n;
            q.push(make_pair(-c2, it->to));
          }
        }
      }
    }
    if (parent[sink] == -1) {
      break;
    }

    int e = f;
    for (int i = sink; i != source; i = parent[i]) {
      e = min(e, capacity[parent[i]][i] - flow[parent[i]][i]);
    }
    for (int i = sink; i != source; i = parent[i]) {
      total.first += e * cost[parent[i]][i];
      flow[parent[i]][i] += e;
      flow[i][parent[i]] -= e;
    }
    f -= e;
    total.second += e;
    for (int i = 0; i < N; i++) {
      h[i] += dist[i];
    }
  }
  return make_pair(total.first, flow);
}/*}}}*/

int main()
{
  int N;
  cin >> N;
  vector<vector<int> > erase(N, vector<int>(N)), write(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> write[i][j];
    }
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> erase[i][j];
    }
  }
  vector<string> grid(N);
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
    int sum = 0;
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == 'o') {
        sum += erase[i][j];
      }
    }
    for (int j = 0; j < N; j++) {
      if (grid[i][j] == 'o') {
        write[i][j] = sum - erase[i][j];
      } else {
        write[i][j] += sum;
      }
    }
  }

  vector<vector<edge> > g(2*N+2);
  const int source = 2*N, sink = 2*N+1;
  for (int i = 0; i < N; i++) {
    const int row = i, col = N+i;
    g[source].push_back(edge(row, 1, 0));
    g[col].push_back(edge(sink, 1, 0));
  }
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      const int row = i, col = N+j;
      g[row].push_back(edge(col, 1, write[i][j]));
      g[col].push_back(edge(row, 0, -write[i][j]));
    }
  }

  const pair<int,vector<vector<int> > > r = primal_dual(g, source, sink);
  cout << r.first << endl;
  const vector<vector<int> >& flow = r.second;
  vector<string> steps;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      const int row = i, col = N+j;
      if (flow[row][col] == 1 && grid[i][j] == '.') {
        ostringstream oss;
        oss << i+1 << " " << j+1 << " write";
        steps.push_back(oss.str());
      } else if (flow[row][col] == 0 && grid[i][j] == 'o') {
        ostringstream oss;
        oss << i+1 << " " << j+1 << " erase";
        steps.push_back(oss.str());
      }
    }
  }
  cout << steps.size() << endl;
  copy(steps.begin(), steps.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}
