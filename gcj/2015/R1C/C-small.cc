#include <iostream>
#include <vector>
#include <set>
using namespace std;

bool ok(const vector<int>& v)
{
  for (int x : v) {
    if (!x) {
      return false;
    }
  }
  return true;
}

void fill(vector<int>& v, int C, int c)
{
  const int V = v.size()-1;
  for (int i = 0; i < C; i++) {
    for (int j = V; j >= 0; j--) {
      if (j-c >= 0 && v[j-c]) {
        v[j] = true;
      }
    }
  }
}

int ans;

void solve2(int C, int V, vector<int> v, set<int>& coins, int depth)
{
  if (ok(v)) {
    ans = min(ans, depth);
  } else if (depth >= ans) {
    // do nothing
  } else {
    for (int i = 1; i <= V; i++) {
      if (!coins.count(i)) {
        coins.insert(i);
        vector<int> w(v);
        fill(w, C, i);
        solve2(C, V, w, coins, depth+1);
        coins.erase(i);
      }
    }
  }
}

int solve(int C, int V, set<int>& coins)
{
  vector<int> v(V+1, false);
  v[0] = true;
  for (int c : coins) {
    fill(v, C, c);
  }

  ans = V;
  solve2(C, V, v, coins, 0);
  return ans;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int C, D, V;
    cin >> C >> D >> V;
    set<int> coins;
    for (int i = 0; i < D; i++) {
      int c;
      cin >> c;
      coins.insert(c);
    }
    cout << "Case #" << Ti << ": " << solve(C, V, coins) << endl;
  }
  return 0;
}
