#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int chinese_postman(const vector<vector<pair<int,int> > >& g)
{
  int total = 0;
  vector<int> odd_nodes;
  for (int i = 0; i < static_cast<int>(g.size()); i++) {
    for (vector<pair<int,int> >::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
      total += it->second;
    }
    if (g[i].size() % 2 == 1) {
      odd_nodes.push_back(i);
    }
  }
  total /= 2;

  const int N = odd_nodes.size();
  vector<vector<int> > w(N, vector<int>(N, -1));
  for (int i = 0; i < N; i++) {
    // dijkstra
    vector<int> dist(g.size(), 1000000);
    dist[odd_nodes[i]] = 0;
    priority_queue<pair<int,int> > q;
    q.push(make_pair(0, odd_nodes[i]));
    while (!q.empty()) {
      const int cost = -q.top().first;
      const int n = q.top().second;
      q.pop();
      for (vector<pair<int,int> >::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        const int c = cost + it->second;
        if (c < dist[it->first]) {
          dist[it->first] = c;
          q.push(make_pair(-c, it->first));
        }
      }
    }
    for (int j = 0; j < N; j++) {
      w[i][j] = dist[odd_nodes[j]];
    }
  }

  vector<int> dp(1<<N, 1000000);
  dp[0] = 0;
  for (int s = 0; s < (1<<N); s++) {
    for (int i = 0; i < N; i++) {
      if (s & (1<<i)) {
        continue;
      }
      for (int j = i+1; j < N; j++) {
        if (s & (1<<j)) {
          continue;
        }
        dp[s | (1<<i) | (1<<j)] = min(dp[s | (1<<i) | (1<<j)], dp[s] + w[i][j]);
      }
    }
  }
  return total + dp[(1<<N)-1];
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int M;
    cin >> M;
    vector<vector<pair<int,int> > > g(N);
    for (int i = 0; i < M; i++) {
      int x, y, w;
      cin >> x >> y >> w;
      --x;  --y;
      g[x].push_back(make_pair(y, w));
      g[y].push_back(make_pair(x, w));
    }
    cout << chinese_postman(g) << endl;
  }
  return 0;
}