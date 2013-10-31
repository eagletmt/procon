#include <iostream>
#include <vector>
#include <map>
using namespace std;

template <class T>
struct renamer
{
  map<T, int> m;
  int operator()(const T& x)
  {
    if (m.count(x)) {
      return m[x];
    } else {
      const int id = next_id();
      m.insert(make_pair(x, id));
      return id;
    }
  }

  int next_id() const { return m.size(); }
};

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

int check(DisjointSet& s, const vector<int>& v, int N)
{
  for (int i = 0; i < N; i++) {
    if (v[i] % 2 != 0 || s.size(i) != N) {
      return 0;
    }
  }
  return 1;
}

void trim(string& s)
{
  size_t i;
  for (i = 0; i < s.size() && s[i] == '0'; i++);
  if (i == s.size()) {
    --i;
  }
  s.erase(0, i);
}

int main()
{
  ios::sync_with_stdio(false);
  int K;
  cin >> K;
  renamer<pair<string,string> > r;
  DisjointSet s(2*K);
  vector<int> v(2*K, 0);
  for (int i = 0; i < K; i++) {
    pair<string,string> p1, p2;
    cin >> p1.first >> p1.second >> p2.first >> p2.second;
    trim(p1.first);
    trim(p1.second);
    trim(p2.first);
    trim(p2.second);
    const int k1 = r(p1), k2 = r(p2);
    ++v[k1];
    ++v[k2];
    s.unite(k1, k2);
  }

  cout << check(s, v, r.next_id()) << endl;
  return 0;
}
