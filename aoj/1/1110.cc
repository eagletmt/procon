#include <iostream>
#include <vector>
using namespace std;

int ans = 20;

void trim(vector<int>& grid)
{
  for (vector<int>::iterator it(grid.begin()); it != grid.end(); ) {
    if (*it == 0) {
      it = grid.erase(it);
    } else {
      ++it;
    }
  }
}

void dfs(const vector<int>& grid)
{
  int N = grid.size();
  ans = min(ans, N);
  if (ans == 0) {
    return;
  }
  for (int i = 0; i < N; i++) {
    // left
    if (i%4 != 0 && grid[i-1] == grid[i]) {
      vector<int> v(grid);
      v[i-1] = v[i] = 0;
      trim(v);
      dfs(v);
      if (ans == 0) {
        return;
      }
    }
    // left-down
    if (i%4 != 0 && i+3 < N && grid[i] == grid[i+3]) {
      vector<int> v(grid);
      v[i+3] = v[i] = 0;
      trim(v);
      dfs(v);
      if (ans == 0) {
        return;
      }
    }
    // down
    if (i+4 < N && grid[i] == grid[i+4]) {
      vector<int> v(grid);
      v[i+4] = v[i] = 0;
      trim(v);
      dfs(v);
      if (ans == 0) {
        return;
      }
    }
    // right-down
    if (i%4 != 3 && i+5 < N && grid[i] == grid[i+5]) {
      vector<int> v(grid);
      v[i+5] = v[i] = 0;
      trim(v);
      dfs(v);
      if (ans == 0) {
        return;
      }
    }
  }
}

int main()
{
  int N;
  cin >> N;
  while (N-- > 0) {
    ans = 20;
    vector<int> grid(20);
    for (int i = 0; i < 20; i++) {
      cin >> grid[i];
    }
    dfs(grid);
    cout << ans << endl;
  }
  return 0;
}
