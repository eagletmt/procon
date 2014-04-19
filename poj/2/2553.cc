#include <cstdio>
#include <vector>
#include <stack>
using namespace std;

void scc_visit(const vector<vector<int> >& g, int v, vector<int>& scc_map, int& scc_size,/*{{{*/
        stack<int>& stk, vector<bool>& in_stk, vector<int>& low, vector<int>& num, int& time)
{
  low[v] = num[v] = ++time;
  stk.push(v);
  in_stk[v] = true;
  for (vector<int>::const_iterator it(g[v].begin()); it != g[v].end(); ++it) {
    const int u = *it;
    if (num[u] == 0) {
      scc_visit(g, u, scc_map, scc_size, stk, in_stk, low, num, time);
      low[v] = min(low[v], low[u]);
    } else if (in_stk[u]) {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) {
    for (;;) {
      const int u = stk.top();
      stk.pop();
      in_stk[u] = false;
      scc_map[u] = scc_size;
      if (u == v) {
        break;
      }
    }
    ++scc_size;
  }
}/*}}}*/

pair<vector<int>,int> strongly_connected_components(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> num(N), low(N);
  stack<int> stk;
  vector<bool> in_stk(N, false);
  int time = 0;
  vector<int> scc_map(N);
  int scc_size = 0;
  for (int v = 0; v < N; v++) {
    if (num[v] == 0) {
      scc_visit(g, v, scc_map, scc_size, stk, in_stk, low, num, time);
    }
  }
  return make_pair(scc_map, scc_size);
}/*}}}*/

int main()
{
  int N;
  while (scanf("%d", &N) == 1 && N != 0) {
    int M;
    scanf("%d", &M);
    vector<vector<int> > g(N);
    for (int i = 0; i < M; i++) {
      int u, v;
      scanf("%d %d", &u, &v);
      --u;  --v;
      g[u].push_back(v);
    }

    const pair<vector<int>, int> r = strongly_connected_components(g);
    const vector<int>& scc_map = r.first;
    vector<bool> has_outedge(r.second, false);
    for (int i = 0; i < N; i++) {
      for (vector<int>::const_iterator it(g[i].begin()); it != g[i].end(); ++it) {
        if (scc_map[i] != scc_map[*it]) {
          has_outedge[scc_map[i]] = true;
        }
      }
    }

    bool first = true;
    for (int i = 0; i < N; i++) {
      if (!has_outedge[scc_map[i]]) {
        if (!first) {
          printf(" ");
        }
        first = false;
        printf("%d", i+1);
      }
    }
    puts("");
  }
  return 0;
}