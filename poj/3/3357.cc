#include <iostream>
#include <sstream>
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
    explicit DisjointSet(int size) : parent(size, -1) {}

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
    if (w != that.w) {
      return w < that.w;
    }
    if (u != that.u) {
      return u < that.u;
    }
    return v < that.v;
  }
};/*}}}*/

template <class Edge>
vector<Edge> kruskal(const vector<Edge>& edges, const int N)/*{{{*/
{
  DisjointSet s(N);
  vector<Edge> used;
  for (typename vector<Edge>::const_iterator it = edges.begin(); it != edges.end() && s.size(0) < N; ++it) {
    if (s.unite(it->u, it->v)) {
      used.push_back(*it);
    }
  }
  return used;
}/*}}}*/

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    cin.ignore();
    vector<edge> edges;
    for (int i = 0; i < N; i++) {
      string line;
      getline(cin, line);
      line.erase(remove(line.begin(), line.end(), ','), line.end());
      istringstream iss(line);
      for (int j = 0; j < N; j++) {
        int w;
        iss >> w;
        if (i < j && w != 0) {
          edges.push_back(edge(i, j, w));
        }
      }
    }
    sort(edges.begin(), edges.end());

    vector<edge> ans = kruskal(edges, N);
    cout << "Case " << Ti << ":" << endl;
    for (vector<edge>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
      cout << char(it->u+'A') << '-' << char(it->v+'A') << ' ' << it->w << endl;
    }
  }
  return 0;
}
