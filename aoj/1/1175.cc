#include <iostream>
#include <map>
#include <algorithm>
#include <cmath>
using namespace std;

double sqr(double x) { return x*x; }

struct circle
{
  int x, y, r, c;
  bool covers(const circle& a) const
  {
    return sqrt(sqr(x - a.x) + sqr(y - a.y)) < r + a.r;
  }
};

int N;
circle cs[24];

map<int,int> memo;
int dfs(int used)
{
  map<int,int>::iterator it = memo.find(used);
  if (it != memo.end()) {
    return it->second;
  }
  int& ans = memo[used];

  ans = 0;
  bool top[24];
  fill_n(top, 24, true);
  for (int i = 0; i < N; i++) {
    if (used & (1<<i)) {
      continue;
    }
    for (int j = i+1; j < N; j++) {
      if (used & (1<<j)) {
        continue;
      }
      if (cs[i].covers(cs[j])) {
        top[j] = false;
      }
    }
  }
  for (int i = 0; i < N; i++) {
    if (used & (1<<i)) {
      continue;
    }
    if (!top[i]) {
      continue;
    }
    for (int j = i+1; j < N; j++) {
      if (used & (1<<j)) {
        continue;
      }
      if (!top[j]) {
        continue;
      }
      if (cs[i].c == cs[j].c) {
        ans = max(ans, 2 + dfs(used | (1<<i) | (1<<j)));
      }
    }
  }
  return ans;
}

int main()
{
  while (cin >> N && N != 0) {
    for (int i = 0; i < N; i++) {
      cin >> cs[i].x >> cs[i].y >> cs[i].r >> cs[i].c;
    }
    memo.clear();
    cout << dfs(0) << endl;
  }
  return 0;
}
