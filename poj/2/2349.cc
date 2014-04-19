#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;

struct DisjointSet/*{{{*/
{
  vector<int> parent;

  int root(int x)
  {
    if (parent[x] < 0) {
      return x;
    } else {
      parent[x] = root(parent[x]);
      return parent[x];
    }
  }

  explicit DisjointSet(int n) : parent(n, -1) {}

  bool unite(int x, int y)
  {
    const int a = root(x);
    const int b = root(y);
    if (a != b) {
      if (parent[a] < parent[b]) {
        parent[a] += parent[b];
        parent[b] = a;
      } else {
        parent[b] += parent[a];
        parent[a] = b;
      }
      return true;
    } else {
      return false;
    }
  }

  bool find(int x, int y) { return root(x) == root(y); }
  int size(int x) { return -parent[root(x)]; }
};/*}}}*/

struct edge
{
  int u, v;
  double w;
  bool operator<(const edge& e) const { return w < e.w; }
};

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int S, N;
    scanf("%d %d", &S, &N);
    vector<P> v(N);
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      v[i] = P(x, y);
    }

    vector<edge> es;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        edge e;
        e.u = i;
        e.v = j;
        e.w = abs(v[i] - v[j]);
        es.push_back(e);
      }
    }
    sort(es.begin(), es.end());
    DisjointSet s(N);
    double ans = 0.0;
    int c = 0;
    for (vector<edge>::const_iterator it = es.begin(); it != es.end() && c < N-S; ++it) {
      if (s.unite(it->u, it->v)) {
        ans = it->w;
        ++c;
      }
    }
    printf("%.2f\n", ans);
  }
  return 0;
}