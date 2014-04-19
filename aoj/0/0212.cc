#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct state {
  int node;
  int ticket;
  int cost;
  state(int n, int t, int c) : node(n), ticket(t), cost(c) {}
  bool operator<(const state& s) const
  {
    return cost > s.cost;
  }
};

int main()
{
  int c, n, m, s, d;
  while (cin >> c >> n >> m >> s >> d && c != 0) {
    --s;  --d;
    vector<vector<pair<int,int> > > g(n);
    for (int i = 0; i < m; i++) {
      int a, b, f;
      cin >> a >> b >> f;
      --a;  --b;
      g[a].push_back(make_pair(b, f));
      g[b].push_back(make_pair(a, f));
    }

    priority_queue<state> q;
    q.push(state(s, c, 0));
    vector<vector<int> > city(n, vector<int>(c+1, 1000000));
    city[s][c] = 0;
    while (!q.empty()) {
      const state s = q.top();
      q.pop();
      if (s.node == d) {
        cout << s.cost << endl;
        break;
      }

      city[s.node][s.ticket] = s.cost;
      for (vector<pair<int,int> >::const_iterator it(g[s.node].begin()); it != g[s.node].end(); ++it) {
        const int next = it->first;
        const int cost = s.cost + it->second;
        if (cost < city[next][s.ticket]) {
          city[next][s.ticket] = cost;
          q.push(state(next, s.ticket, cost));
        }
        if (s.ticket > 0) {
          const int cost2 = s.cost + it->second/2;
          if (cost2 < city[next][s.ticket-1]) {
            city[next][s.ticket-1] = cost2;
            q.push(state(next, s.ticket-1, cost2));
          }
        }
      }
    }
  }
  return 0;
}
