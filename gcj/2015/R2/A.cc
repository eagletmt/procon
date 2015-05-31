#include <iostream>
#include <vector>
using namespace std;

struct impossible {};

bool check(int R, int C, vector<string>& grid, int r, int c, int dr, int dc)
{
  r += dr;
  c += dc;
  while (r >= 0 && r < R && c >= 0 && c < C) {
    if (grid[r][c] != '.') {
      return true;
    }
    r += dr;
    c += dc;
  }
  return false;
}

int solve(int R, int C, vector<string>& grid)
try {
  int cnt = 0;

  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      if (grid[i][j] == '<') {
        ++cnt;
        if (!check(R, C, grid, i, j, -1, 0) && !check(R, C, grid, i, j, 0, 1) && !check(R, C, grid, i, j, 1, 0)) {
          throw impossible();
        }
        break;
      } else if (grid[i][j] != '.') {
        break;
      }
    }

    for (int j = C-1; j >= 0; j--) {
      if (grid[i][j] == '>') {
        ++cnt;
        if (!check(R, C, grid, i, j, -1, 0) && !check(R, C, grid, i, j, 0, -1) && !check(R, C, grid, i, j, 1, 0)) {
          throw impossible();
        }
        break;
      } else if (grid[i][j] != '.') {
        break;
      }
    }
  }

  for (int j = 0; j < C; j++) {
    for (int i = 0; i < R; i++) {
      if (grid[i][j] == '^') {
        ++cnt;
        if (!check(R, C, grid, i, j, 0, 1) && !check(R, C, grid, i, j, 1, 0) && !check(R, C, grid, i, j, 0, -1)) {
          throw impossible();
        }
        break;
      } else if (grid[i][j] != '.') {
        break;
      }
    }

    for (int i = R-1; i >= 0; i--) {
      if (grid[i][j] == 'v') {
        ++cnt;
        if (!check(R, C, grid, i, j, 0, 1) && !check(R, C, grid, i, j, -1, 0) && !check(R, C, grid, i, j, 0, -1)) {
          throw impossible();
        }
        break;
      } else if (grid[i][j] != '.') {
        break;
      }
    }
  }

  return cnt;
} catch (impossible&) {
  return -1;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int R, C;
    cin >> R >> C;
    vector<string> grid(R);
    for (int i = 0; i < R; i++) {
      cin >> grid[i];
    }
    int ans = solve(R, C, grid);
    cout << "Case #" << Ti << ": ";
    if (ans < 0) {
      cout << "IMPOSSIBLE";
    } else {
      cout << ans;
    }
    cout << endl;
  }
  return 0;
}
