#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

bool augument(const vector<vector<int> >& g, int u, vector<int>& xm, vector<int>& ym, vector<bool>& visited) // {{{
{
  if (u < 0) {
    return true;
  }

  for (vector<int>::const_iterator it(g[u].begin()); it != g[u].end(); ++it) {
    if (!visited[*it]) {
      visited[*it] = true;
      if (augument(g, ym[*it], xm, ym, visited)) {
        xm[u] = *it;
        ym[*it] = u;
        return true;
      }
    }
  }
  return false;
} // }}}

int bipartite_matching(const vector<vector<int> >& g)  // {{{
{
  const int N = g.size();
  vector<int> xm(N, -1), ym(N, -1);
  int match = 0;
  for (int u = 0; u < N; u++) {
    if (xm[u] == -1) {
      vector<bool> visited(N, false);
      if (augument(g, u, xm, ym, visited)) {
        match++;
      }
    }
  }
  return match;
} // }}}

struct task
{
  int start, end;
  pair<int,int> from, to;
};

int dist(const pair<int,int>& a, const pair<int,int>& b)
{
  return abs(a.first - b.first) + abs(a.second - b.second);
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    vector<task> tasks(N);
    for (int i = 0; i < N; i++) {
      string t;
      cin >> t >> tasks[i].from.first >> tasks[i].from.second >> tasks[i].to.first >> tasks[i].to.second;
      tasks[i].start = (10*(t[0]-'0') + t[1]-'0')*60 + (10*(t[3]-'0') + t[4]-'0');
      tasks[i].end = tasks[i].start + dist(tasks[i].from, tasks[i].to);
    }

    vector<vector<int> > g(N);
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        if (tasks[i].end + dist(tasks[i].to, tasks[j].from) < tasks[j].start) {
          g[i].push_back(j);
        }
      }
    }
    cout << N - bipartite_matching(g) << endl;
  }
  return 0;
}
