#include <cstdio>
#include <vector>
#include <algorithm>
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

    bool find(int x, int y) { return root(x) == root(y); }
    int size(int x) { return -parent[root(x)]; }
};/*}}}*/

struct edge {/*{{{*/
  int u, v;
  typedef int weight_type;
  weight_type w;
  edge() {}
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const { return w < that.w; }
};/*}}}*/

pair<int, vector<pair<int,int> > >
kruskal(const vector<edge>& edges, const int N)/*{{{*/
{
  DisjointSet s(N);
  int ans = 0;
  vector<pair<int,int> > es;
  for (vector<edge>::const_iterator it(edges.begin()); it != edges.end() && s.size(0) < N; ++it) {
    if (s.unite(it->u, it->v)) {
      ans = max(ans, it->w);
      es.push_back(make_pair(it->u, it->v));
    }
  }
  return make_pair(ans, es);
}/*}}}*/

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  vector<edge> es(M);
  for (int i = 0; i < M; i++) {
    scanf("%d %d %d", &es[i].u, &es[i].v, &es[i].w);
    --es[i].u;  --es[i].v;
  }
  sort(es.begin(), es.end());
  const pair<int,vector<pair<int,int> > > p = kruskal(es, N);
  printf("%d\n", p.first);
  printf("%lu\n", p.second.size());
  for (vector<pair<int,int> >::const_iterator it(p.second.begin()); it != p.second.end(); ++it) {
    printf("%d %d\n", it->first+1, it->second+1);
  }
  return 0;
}