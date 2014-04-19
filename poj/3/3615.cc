#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

struct Node {
  int index;
  int cost;
  Node(int i, int c) : index(i), cost(c)
  {}

  bool operator<(const Node& n) const
  {
    return cost > n.cost;
  }
};

vector<vector<int> > floyd(const vector<vector<int> >& g, const vector<vector<int> >& w)
{
  const int N = g.size();
  vector<vector<int> > dist(N+1, vector<int>(N+1, numeric_limits<int>::max()));
  for (int i = 1; i <= N; i++) {
    for (int j = 0; j < g[i].size(); j++) {
      const int to = g[i][j];
      dist[i][to] = w[i][j];
    }
  }

  for (int k = 1; k <= N; k++) {
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= N; j++) {
        dist[i][j] = min(dist[i][j], max(dist[i][k], dist[k][j]));
      }
    }
  }
  return dist;
}

int main()
{
  int N, M, T;
  cin >> N >> M >> T;
  vector<vector<int> > g(N+1);
  vector<vector<int> > w(N+1);
  for (int i = 0; i < M; i++) {
    int s, e, h;
    cin >> s >> e >> h;
    g[s].push_back(e);
    w[s].push_back(h);
  }

  const vector<vector<int> > dist = floyd(g, w);
  for (int i = 0; i < T; i++) {
    int a, b;
    cin >> a >> b;
    int c = dist[a][b];
    if (c == numeric_limits<int>::max()) {
      cout << -1 << endl;
    } else {
      cout << c << endl;
    }
  }
  return 0;
}
