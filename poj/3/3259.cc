#include <iostream>
#include <vector>
#include <iterator>
#include <limits>
using namespace std;

struct Edge {
  int src, dst, weight;
  Edge(int s, int d, int w) : src(s), dst(d), weight(w) {}
};

bool bellman_ford(const vector<Edge>& g, int N, int start)
{
  vector<int> dist(N, 100000);
  dist[start] = 0;

  for (int i = 0; i < N; i++) {
    for (vector<Edge>::const_iterator it(g.begin()); it != g.end(); ++it) {
      if (dist[it->src] + it->weight < dist[it->dst]) {
        dist[it->dst] = dist[it->src] + it->weight;
      }
    }
  }

  for (vector<Edge>::const_iterator it(g.begin()); it != g.end(); ++it) {
    if (dist[it->src] + it->weight < dist[it->dst]) {
      return true;
    }
  }
  return false;
}

int main(void)
{
  int F, N, M, W;

  cin >> F;
  while (F-- > 0) {
    cin >> N >> M >> W;
    vector<Edge> edges;
    for (int i = 0; i < M; i++) {
      int s, d, w;
      cin >> s >> d >> w;

      edges.push_back(Edge(s, d, w));
      edges.push_back(Edge(d, s, w));
    }
    for (int i = 0; i < W; i++) {
      int s, d, w;
      cin >> s >> d >> w;
      edges.push_back(Edge(s, d, -w));
    }

    cout << (bellman_ford(edges, N, 1) ? "YES" : "NO") << endl;
  }
  return 0;
}
