#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class DisjointSet {/*{{{*/
  private:
    vector<int> parent;

    int root(int x)
    {
      if (parent[x] < 0) {
        return x;
      } else {
        return parent[x] = root(parent[x]);
      }
    }

  public:
    DisjointSet(int n) : parent(n, -1) {}

    bool unite(int x, int y)
    {
      x = root(x);
      y = root(y);
      if (x != y) {
        if (parent[x] > parent[y]) {
          swap(x, y);
        }
        parent[x] += parent[y];
        parent[y] = x;
        return true;
      } else {
        return false;
      }
    }

    bool find(int x, int y)
    {
      return root(x) == root(y);
    }

    int size(int n)
    {
      return -parent[root(n)];
    }
};/*}}}*/

struct edge {
  int u, v, w;
  bool operator<(const edge& e) const
  {
    return w < e.w;
  }
};

int solve(int N, const vector<edge>& edges)
{
  int ans = numeric_limits<int>::max();
  for (vector<edge>::const_iterator it(edges.begin()); it != edges.end(); ++it) {
    DisjointSet s(N);
    s.unite(it->u, it->v);
    int w = 0;
    for (vector<edge>::const_iterator jt(it+1); s.size(0) < N; ++jt) {
      if (jt == edges.end()) {
        goto FAIL;
      }
      if (s.unite(jt->u, jt->v)) {
        w = max(w, jt->w - it->w);
      }
    }
    ans = min(ans, w);
FAIL:
    ;
  }
  return ans == numeric_limits<int>::max() ? -1 : ans;
}

int main()
{
  int n, m;
  while (cin >> n >> m && n != 0) {
    vector<edge> edges(m);
    for (int i = 0; i < m; i++) {
      cin >> edges[i].u >> edges[i].v >> edges[i].w;
      --edges[i].u; --edges[i].v;
    }
    sort(edges.begin(), edges.end());
    cout << solve(n, edges) << endl;
  }
  return 0;
}
