#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

int dijkstra(const vector<vector<pair<int,int> > >& g, int start, int goal)
{
  const int N = g.size();
  vector<int> costs1(N, numeric_limits<int>::max()), costs2(N, numeric_limits<int>::max());
  priority_queue<pair<int, int> > q;
  q.push(make_pair(0, start));
  while (!q.empty()) {
    const int cost = -q.top().first;
    const int node = q.top().second;
    q.pop();
    if (costs2[node] <= cost) {
      continue;
    }
    if (costs1[node] > cost) {
      costs1[node] = cost;
    } else {
      costs2[node] = cost;
    }

    for (vector<pair<int,int> >::const_iterator it(g[node].begin()); it != g[node].end(); ++it) {
      q.push(make_pair(-(cost + it->second), it->first));
    }
  }
  return costs2[goal];
}

int main()
{
  int N, R;
  cin >> N >> R;
  vector<vector<pair<int, int> > > g(N);
  for (int i = 0; i < R; i++) {
    int a, b, d;
    cin >> a >> b >> d;
    g[a-1].push_back(make_pair(b-1, d));
    g[b-1].push_back(make_pair(a-1, d));
  }
  cout << dijkstra(g, 0, N-1) << endl;
  return 0;
}
