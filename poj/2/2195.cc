#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>
using namespace std;

struct node
{
  int index;
  int capacity;
  int cost;
  node(int i, int c, int d) : index(i), capacity(c), cost(d) {}
};

pair<int,int> primal_dual(const vector<vector<node> >& g, int source, int sink)
{
  const int N = g.size();
  vector<vector<int> > capacity(N, vector<int>(N, 0)), cost(N, vector<int>(N, 0)), flow(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (vector<node>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      capacity[i][it->index] += it->capacity;
      cost[i][it->index] += it->cost;
    }
  }
  pair<int,int> total;  // (cost, flow)
  vector<int> h(N, 0);
  for (int f = numeric_limits<int>::max(); f > 0; ) {
    vector<int> dist(N, 1000000);
    dist[source] = 0;
    vector<int> parent(N, -1);
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, source));
    while (!q.empty()) {
      const int n = q.top().second;
      const int c = -q.top().first;
      q.pop();
      for (vector<node>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (capacity[n][it->index] - flow[n][it->index] > 0) {
          const int c2 = c + cost[n][it->index] + h[n] - h[it->index];
          if (c2 < dist[it->index]) {
            dist[it->index] = c2;
            parent[it->index] = n;
            q.push(make_pair(-c2, it->index));
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
  return total;
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<pair<int,int> > men, houses;
    for (int i = 0; i < N; i++) {
      string line;
      cin >> line;
      for (int j = 0; j < M; j++) {
        if (line[j] == 'H') {
          houses.push_back(make_pair(i, j));
        } else if (line[j] == 'm') {
          men.push_back(make_pair(i, j));
        }
      }
    }

    const int A = men.size();
    const int B = houses.size();
    vector<vector<node> > g(A+B+2);
    for (int i = 0; i < A; i++) {
      // source -> man
      g[A+B].push_back(node(i, 1, 0));
      g[i].push_back(node(A+B, 0, 0));
    }
    for (int j = 0; j < B; j++) {
      // house -> sink
      g[A+j].push_back(node(A+B+1, 1, 0));
      g[A+B+1].push_back(node(A+j, 0, 0));
    }
    for (int i = 0; i < A; i++) {
      for (int j = 0; j < B; j++) {
        // man -> house
        const int c = abs(men[i].first - houses[j].first) + abs(men[i].second - houses[j].second);
        g[i].push_back(node(A+j, 1, c));
        g[A+j].push_back(node(i, 0, -c));
      }
    }

    const pair<int,int> ans = primal_dual(g, A+B, A+B+1);
    cout << ans.first << endl;
  }
  return 0;
}
