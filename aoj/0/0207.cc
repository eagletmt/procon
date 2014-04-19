#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool is_maze(vector<vector<int> > grid, const pair<int,int>& start, const pair<int,int>& goal)
{
  const int W = grid.size();
  const int H = grid[0].size();
  const int color = grid[start.first][start.second];
  queue<pair<int,int> > q;
  q.push(start);
  grid[start.first][start.second] = -1;
  while (!q.empty()) {
    const pair<int,int> p = q.front();
    q.pop();
    if (p == goal) {
      return true;
    }

    for (int d = 0; d < 4; d++) {
      static const int dir_w[] = {-1, 1, 0, 0};
      static const int dir_h[] = {0, 0, -1, 1};
      const int next_w = p.first + dir_w[d];
      const int next_h = p.second + dir_h[d];
      if (next_w >= 0 && next_w < W && next_h >= 0 && next_h < H
          && grid[next_w][next_h] == color) {
        q.push(make_pair(next_w, next_h));
        grid[next_w][next_h] = -1;
      }
    }
  }
  return false;
}

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<vector<int> > grid(W, vector<int>(H, 0));
    pair<int,int> start, goal;
    cin >> start.first >> start.second;
    --start.first;  --start.second;
    cin >> goal.first >> goal.second;
    --goal.first; --goal.second;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++) {
      int c, d, x, y;
      cin >> c >> d >> x >> y;
      --x;  --y;
      if (d == 1) {
        // vert
        for (int i = 0; i < 4; i++) {
          grid[x][y+i] = grid[x+1][y+i] = c;
        }
      } else {
        // horiz
        for (int i = 0; i < 4; i++) {
          grid[x+i][y] = grid[x+i][y+1] = c;
        }
      }
    }
    cout << (is_maze(grid, start, goal) ? "OK" : "NG") << endl;
  }
  return 0;
}
