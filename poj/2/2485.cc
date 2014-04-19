#include <cstdio>
#include <vector>
#include <queue>
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
  typedef int weight_type;
  weight_type w;
  edge(int s, int d, weight_type w_) : u(s), v(d), w(w_) {}
  bool operator<(const edge& that) const
  {
    return w > that.w;
  }
};/*}}}*/

template <class Edge>
typename Edge::weight_type kruskal(priority_queue<Edge>& edges, const int N)/*{{{*/
{
  DisjointSet s(N);
  int ans;
  while (s.size(0) < N && !edges.empty()) {
    const Edge e = edges.top();
    edges.pop();
    if (s.unite(e.u, e.v)) {
      ans = e.w;
    }
  }
  return ans;
}/*}}}*/

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    priority_queue<edge> q;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int w;
        scanf("%d", &w);
        if (i < j) {
          q.push(edge(i, j, w));
        }
      }
    }
    printf("%d\n", kruskal(q, N));
  }
  return 0;
}