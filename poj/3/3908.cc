#include <iostream>
#include <vector>
using namespace std;

class DisjointSet/*{{{*/
{
  public:
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

int main()
{
  int N;
  while (cin >> N) {
    DisjointSet s(N);
    int yes = 0, no = 0;
    string cmd;
    vector<int> towns(N);
    for (int i = 0; i < N; i++) {
      towns[i] = i;
    }
    while (cin >> cmd && cmd != "e") {
      if (cmd == "c") {
        int i, j;
        cin >> i >> j;
        --i;  --j;
        s.unite(towns[i], towns[j]);
      } else if (cmd == "d") {
        int i;
        cin >> i;
        --i;
        towns[i] = s.parent.size();
        s.parent.push_back(-1);
      } else if (cmd == "q") {
        int i, j;
        cin >> i >> j;
        --i;  --j;
        if (s.find(towns[i], towns[j])) {
          ++yes;
        } else {
          ++no;
        }
      }
    }
    cout << yes << " , " << no << endl;
  }
  return 0;
}