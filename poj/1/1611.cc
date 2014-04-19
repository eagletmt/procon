#include <iostream>
#include <vector>
#include <algorithm>

class counting {
  private:
    int n;
  public:
    counting(int from = 0) : n(from) {}
    int operator()() {
      return n++;
    }
};

class DisjointSet {
  private:
    std::vector<int> rank;
    std::vector<int> parent;

    int root(int x)
    {
      if (x == parent[x]) {
        return x;
      } else {
        parent[x] = root(parent[x]);
        return parent[x];
      }
    }

  public:
    DisjointSet(int size)
      : rank(size, 1), parent(size)
    {
      std::generate(parent.begin(), parent.end(), counting());
    }

    bool find(int x, int y)
    {
      return root(x) == root(y);
    }

    void unite(int x, int y)
    {
      int a = root(x);
      int b = root(y);

      if (a != b) {
        if (rank[a] < rank[b]) {
          rank[a] += rank[b];
          parent[b] = a;
        } else {
          rank[b] += rank[a];
          parent[a] = b;
        }
      }
    }

    int count(int x)
    {
      int a = root(x);
      return rank[a];
    }
};

int main(void)
{
  for (;;) {
    int n, m;
    std::cin >> n >> m;
    if (n == 0 && m == 0) {
      break;
    }

    DisjointSet u(n);
    for (int i = 0; i < m; i++) {
      int k;
      std::cin >> k;
      int a;
      std::cin >> a;
      for (int j = 1; j < k; j++) {
        int b;
        std::cin >> b;
        u.unite(a, b);
      }
    }
    std::cout << u.count(0) << std::endl;
  }

  return 0;
}
