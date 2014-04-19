#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <limits>
using namespace std;

vector<int> dijkstra(const vector<vector<pair<int, int> > >& g, int start)
{
  const int N = g.size();
  vector<int> dists(N, 0);
  vector<bool> done(N, false);
  priority_queue<pair<int,int> > q;
  q.push(make_pair(numeric_limits<int>::max(), start));
  while (!q.empty()) {
    const int dist = q.top().first;
    const int from = q.top().second;
    q.pop();
    if (done[from]) {
      continue;
    }
    done[from] = true;

    for (vector<pair<int,int> >::const_iterator it(g[from].begin()); it != g[from].end(); ++it) {
      const int d = min(dist, it->second);
      if (d > dists[it->first]) {
        dists[it->first] = d;
        q.push(make_pair(d, it->first));
      }
    }
  }
  return dists;
}

int main()
{
  int n, r;
  int scenario = 0;
  while (cin >> n >> r && n != 0) {
    map<string, int> cities;
    vector<vector<pair<int, int> > > g(n);

    for (int i = 0; i < r; i++) {
      string s, t;
      int w;
      cin >> s >> t >> w;
      int a;
      if (cities.count(s) == 0) {
        a = cities.size();
        cities.insert(make_pair(s, a));
      } else {
        a = cities[s];
      }
      int b;
      if (cities.count(t) == 0) {
        b = cities.size();
        cities.insert(make_pair(t, b));
      } else {
        b = cities[t];
      }
      g[a].push_back(make_pair(b, w));
      g[b].push_back(make_pair(a, w));
    }

    string s, t;
    cin >> s >> t;
    vector<int> dists(dijkstra(g, cities[s]));

    cout << "Scenario #" << ++scenario << endl;
    cout << dists[cities[t]] << " tons" << endl;
    cout << endl;
  }
  return 0;
}
