#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct state {
  //vector<int> dir;
  int cost;
  int index;

  bool operator<(const state& s) const
  {
    return cost > s.cost;
  }
};

int main()
{
  int N, A, B;
  cin >> N >> A >> B;
  A--;
  B--;
  vector<vector<int> > g(N);
  for (int i = 0; i < N; i++) {
    int k;
    cin >> k;
    g[i].resize(k);
    for (int j = 0; j < k; j++) {
      cin >> g[i][j];
      g[i][j]--;
    }
  }

  vector<int> cost(N, 1000000);
  priority_queue<state> q;
  state s;
  s.index = A;
  s.cost = cost[A] = 0;
  q.push(s);
  while (!q.empty()) {
    state t = q.top();
    q.pop();
    if (t.index == B) {
      cout << t.cost << endl;
      return 0;
    }

    for (int i = 0; i < g[t.index].size(); i++) {
      int to = g[t.index][i];
      int c = t.cost + (i == 0 ? 0 : 1);
      //cerr << t.index+1 << " -> " << to+1 << ": " << c << endl;
      if (c < cost[to]) {
        cost[to] = c;
        state u(t);
        u.index = to;
        u.cost = c;
        q.push(u);
      }
    }
  }
  cout << -1 << endl;
  return 0;
}
