#include <iostream>
#include <vector>
using namespace std;

static const int INF = 10000000;

int solve2(int R, int C, unsigned s)
{
  vector<vector<int> > grid(R, vector<int>(C, false));
  for (int i = 0; i < R*C; i++) {
    if (s & (1U<<i)) {
      grid[i/C][i%C] = true;
    }
  }

  int ans = 0;
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (j < C-1 && grid[i][j] && grid[i][j+1]) {
        ++ans;
      }
      if (i < R-1 && grid[i][j] && grid[i+1][j]) {
        ++ans;
      }
    }
  }
  return ans;
}

int solve(int R, int C, int N)
{
  int ans = INF;
  for (unsigned s = 0; s < (1U<<(R*C)); s++) {
    if (__builtin_popcount(s) == N) {
      ans = min(ans, solve2(R, C, s));
    }
  }
  return ans;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int R, C, N;
    cin >> R >> C >> N;

    cout << "Case #" << Ti << ": " << solve(R, C, N) << endl;
  }
  return 0;
}
