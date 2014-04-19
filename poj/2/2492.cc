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
};/*}}}*/

int main()
{
  int T;
  scanf("%d", &T);
  for (int t = 1; t <= T; t++) {
    int N, M;
    scanf("%d %d", &N, &M);
    DisjointSet s(N);
    vector<int> opposite(N, -1);
    bool suspicious = false;
    for (int i = 0; i < M; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      --x;  --y;
      if (suspicious) {
        continue;
      }
      if (s.find(x, y)) {
        suspicious = true;
      } else {
        if (opposite[x] == -1) {
          opposite[x] = y;
        } else {
          s.unite(opposite[x], y);
        }
        if (opposite[y] == -1) {
          opposite[y] = x;
        } else {
          s.unite(x, opposite[y]);
        }
      }
    }
    printf("Scenario #%d:\n", t);
    if (suspicious) {
      puts("Suspicious bugs found!\n");
    } else {
      puts("No suspicious bugs found!\n");
    }
  }
  return 0;
}