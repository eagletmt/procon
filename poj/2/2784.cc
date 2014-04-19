#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

class DisjointSet/*{{{*/
{
  private:
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

  public:
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

    bool find(int x, int y)
    {
      return root(x) == root(y);
    }

    int size(int x)
    {
      return -parent[root(x)];
    }
};/*}}}*/

struct edge {/*{{{*/
  int u, v;
  int w;
  edge(int s, int d, int w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const
  {
    return w < that.w;
  }
};/*}}}*/

int kruskal(const vector<edge> edges, int N, DisjointSet& s, int upper)/*{{{*/
{
  int ttl = 0;
  for (vector<edge>::const_iterator it(edges.begin()); it != edges.end() && s.size(0) < N; ++it) {
    if (s.unite(it->u, it->v)) {
      ttl += it->w;
      if (ttl >= upper) {
        return ttl;
      }
    }
  }
  return ttl;
}/*}}}*/

int solve(const vector<pair<vector<int>,int> >& subnetworks, const vector<pair<int,int> >& ps)
{
  const int N = ps.size();
  vector<edge> edges;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      const int x = ps[i].first - ps[j].first;
      const int y = ps[i].second - ps[j].second;
      edges.push_back(edge(i, j, x*x + y*y));
    }
  }
  sort(edges.begin(), edges.end());

  int ans = numeric_limits<int>::max();
  const int Q = subnetworks.size();
  for (int b = 0; b < (1<<Q); b++) {
    DisjointSet s(N);
    int c = 0;
    for (vector<bool>::size_type i = 0; i < subnetworks.size(); i++) {
      if (b & (1 << i)) {
        for (vector<int>::const_iterator it(subnetworks[i].first.begin()); it+1 != subnetworks[i].first.end(); ++it) {
          s.unite(*it, *(it+1));
        }
        c += subnetworks[i].second;
      }
    }
    c += kruskal(edges, N, s, ans);
    ans = min(ans, c);
  }
  return ans;
}

int main()
{
  int n, q;
  cin >> n >> q;
  vector<pair<vector<int>,int> > subnetworks(q);
  for (int i = 0; i < q; i++) {
    int m;
    cin >> m >> subnetworks[i].second;
    subnetworks[i].first.resize(m);
    for (int j = 0; j < m; j++) {
      cin >> subnetworks[i].first[j];
      --subnetworks[i].first[j];
    }
  }
  vector<pair<int,int> > ps(n);
  for (int i = 0; i < n; i++) {
    cin >> ps[i].first >> ps[i].second;
  }
  cout << solve(subnetworks, ps) << endl;
  return 0;
}