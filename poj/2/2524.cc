#include <cstdio>
#include <vector>
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
    bool is_top(int x) const { return parent[x] < 0; }
};/*}}}*/

int main()
{
  int T = 0;
  int N, M;
  while (scanf("%d %d", &N, &M) == 2 && N != 0) {
    DisjointSet s(N);
    for (int i = 0; i < M; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      --x;  --y;
      s.unite(x, y);
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
      if (s.is_top(i)) {
        ++ans;
      }
    }
    printf("Case %d: %d\n", ++T, ans);
  }
  return 0;
}