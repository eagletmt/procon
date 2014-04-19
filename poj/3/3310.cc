#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool caterpillar(const vector<vector<int> >& g)
{
  for (int i = 0; i < g.size(); i++) {
    set<int> visited;

    visited.insert(i);
    int cur = i;
    while (visited.size() != g.size()) {
      const vector<int> n = g[cur];
      if (n.size() == 0) {
        goto NEXT;
      }
      int next = -1;
      for (int j = 0; j < n.size(); j++) {
        const int node = n[j];
        if (g[node].size() == 1 && g[node][0] == cur) {
          visited.insert(node);
        } else if (visited.find(node) != visited.end()) {
          // already visited
        } else {
          if (next != -1) {
            // not caterpillar from this node cur
            goto NEXT;
          }
          else {
            next = node;
            visited.insert(node);
          }
        }
      }
      if (next == -1) {
        return visited.size() == g.size();
      }
      cur = next;
    }
    return true;
NEXT:
    ;
  }
  return false;
}

#if 0
void test1()
{
  vector<vector<int> > v(22);
  int input[] = {1,2,2,3,2,4,2,5,2,6,6,7,6,10,10,8,9,10,10,12,11,12,12,13,12,17,18,17,15,17,15,14,16,15,17,20,20,21,20,22,20,19};
  for (int i = 0; i < 42; i += 2) {
    v[input[i]-1].push_back(input[i+1]-1);
    v[input[i+1]-1].push_back(input[i]-1);
  }
  cout << caterpillar(v) << endl;
}
void test2()
{
  vector<vector<int> > v(16);
  int input[] = {1,2,2,3,5,2,4,2,2,6,6,7,6,8,6,9,9,10,10,12,10,11,10,14,10,13,13,16,13,15};
  for (int i = 0; i < 30; i += 2) {
    v[input[i]-1].push_back(input[i+1]-1);
    v[input[i+1]-1].push_back(input[i]-1);
  }
  cout << caterpillar(v) << endl;
}
#endif

int main()
{
  int c = 1;
  int n, m;
  while (cin >> n && n != 0 && cin >> m) {
    vector<vector<int> > g(n);
    for (int i = 0; i < m; i++) {
      int a, b;
      cin >> a >> b;
      g[a-1].push_back(b-1);
      g[b-1].push_back(a-1);
    }
    cout << "Graph " << c << " is ";
    if (!caterpillar(g)) {
      cout << "not ";
    }
    cout << "a caterpillar." << endl;
    c++;
  }
  return 0;
}
