#include <iostream>
#include <vector>
#include <map>
using namespace std;

struct S
{
  int base;
  int size;
  int dim;
  vector<pair<int,int> > bounds;

  int calc(const vector<int>& is) const
  {
    vector<int> c(dim+1);
    c[dim] = size;
    for (int i = dim-1; i > 0; i--) {
      c[i] = c[i+1]*(bounds[i].second - bounds[i].first + 1);
    }
    c[0] = base;
    for (int i = 0; i < dim; i++) {
      c[0] -= c[i+1]*bounds[i].first;
    }

    int addr = c[0];
    for (int i = 0; i < dim; i++) {
      addr += c[i+1]*is[i];
    }
    return addr;
  }
};

int main()
{
  int N, R;
  cin >> N >> R;
  map<string, S> arrays;
  for (int i = 0; i < N; i++) {
    string name;
    S s;
    cin >> name >> s.base >> s.size >> s.dim;
    for (int j = 0; j < s.dim; j++) {
      int u, l;
      cin >> u >> l;
      s.bounds.push_back(make_pair(u, l));
    }
    arrays.insert(make_pair(name, s));
  }

  for (int i = 0; i < R; i++) {
    string name;
    cin >> name;
    const S s = arrays.find(name)->second;
    vector<int> is;
    for (int j = 0; j < s.dim; j++) {
      int x;
      cin >> x;
      is.push_back(x);
    }

    cout << name << "[";
    for (int j = 0; j < s.dim; j++) {
      if (j != 0) {
        cout << ", ";
      }
      cout << is[j];
    }
    cout << "] = " << s.calc(is) << endl;
  }
  return 0;
}