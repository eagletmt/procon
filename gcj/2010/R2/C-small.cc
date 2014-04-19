#include <iostream>
#include <vector>
using namespace std;

static const int max_i = 100, max_j = 100;
typedef bool grid_type[max_i][max_j];

bool finished(const grid_type grid)
{
  for (int i = 0; i < max_i; i++) {
    for (int j = 0; j < max_j; j++) {
      if (grid[i][j]) {
        return false;
      }
    }
  }
  return true;
}

void step(grid_type grid)
{
  grid_type old;
  for (int i = 0; i < max_i; i++) {
    for (int j = 0; j < max_j; j++) {
      old[i][j] = grid[i][j];
      }
  }

  for (int i = 0; i < max_i; i++) {
    for (int j = 0; j < max_j; j++) {
      if (old[i][j]) {
        // die
        if ((i == 0 || !old[i-1][j]) && (j == 0 || !old[i][j-1])) {
          grid[i][j] = false;
        }
      } else {
        // born
        if ((i != 0 && old[i-1][j]) && (j != 0 && old[i][j-1])) {
          grid[i][j] = true;
        }
      }
    }
  }
}

void print_grid(const grid_type grid)
{
  for (int i = 0; i < max_i; i++) {
    for (int j = 0; j < max_j; j++) {
      cout << (grid[i][j] ? 1 : 0) << ' ';
    }
    cout << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    grid_type grid;
    for (int i = 0; i < max_i; i++) {
      for (int j = 0; j < max_j; j++) {
        grid[i][j] = false;
      }
    }
    int R;
    cin >> R;
    for (int i = 0; i < R; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      x1--; y1--; x2--; y2--;

      //cout << x1 << ' ' << y1 << ' ' << x2 << ' ' << y2 << endl;
      for (int x = x1; x <= x2; x++) {
        for (int y = y1; y <= y2; y++) {
          grid[y][x] = true;
        }
      }
    }

    int ans = 0;
    //print_grid(grid); cout << endl;
    while (!finished(grid)) {
      step(grid);
      //print_grid(grid); //cout << endl;
      ans++;
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}

