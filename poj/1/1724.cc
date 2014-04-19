#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Node {
  int index, distance, cost;

  Node(int i, int d, int c) : index(i), distance(d), cost(c) {}
  bool operator<(const Node& n) const
  {
    return distance == n.distance ? cost > n.cost : distance > n.distance;
  }
};

int dijkstra(const vector<vector<Node> >& g, int start, int goal, int max_cost)
{
  static const int MAX = 1000000;
  priority_queue<Node> q;
  vector<int> dist(g.size(), MAX);
  q.push(Node(start, 0, 0));
  dist[0] = 0;
  while (!q.empty()) {
    const Node n = q.top();
    q.pop();
    dist[n.index] = n.distance;
    if (n.index == goal) {
      return dist[goal];
    }

    for (int i = 0; i < g[n.index].size(); i++) {
      const Node to = g[n.index][i];
      if (n.cost + to.cost <= max_cost) {
        q.push(Node(to.index, n.distance + to.distance, n.cost + to.cost));
      }
    }
  }
  if (dist[goal] == MAX) {
    return -1;
  } else {
    return dist[goal];
  }
}

int main()
{
  int K, N, R;
  cin >> K >> N >> R;
  
  vector<vector<Node> > g(N);
  for (int i = 0; i < R; i++) {
    int S, D, L, T;
    cin >> S >> D >> L >> T;
    S--;
    D--;
    g[S].push_back(Node(D, L, T));
  }
  cout << dijkstra(g, 0, N-1, K) << endl;
  return 0;
}
