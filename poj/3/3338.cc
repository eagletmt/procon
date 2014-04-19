#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

struct rect
{
  int left, right, upper, lower;
  rect() {}
  rect(int h1, int w1, int h2, int w2)
    : left(min(h1, h2)), right(max(h1, h2))
    , upper(max(w1, w2)), lower(min(w1, w2))
  {}
};

int bfs(const vector<vector<bool> >& grid)
{
  const int W = grid.size();
  const int H = grid[0].size();
  int ans = 0;
  vector<vector<bool> > visited(W, vector<bool>(H, false));
  for (int i = 0; i < W; i++) {
    for (int j = 0; j < H; j++) {
      if (grid[i][j] && !visited[i][j]) {
        ++ans;
        queue<pair<int,int> > q;
        q.push(make_pair(i, j));
        visited[i][j] = true;
        while (!q.empty()) {
          const pair<int,int> p = q.front();
          q.pop();
          for (int d = 0; d < 4; d++) {
            static const int di[] = {-1, 1, 0, 0};
            static const int dj[] = {0, 0, -1, 1};
            const int k = p.first + di[d];
            const int l = p.second + dj[d];
            if (grid[k][l] && !visited[k][l]) {
              visited[k][l] = true;
              q.push(make_pair(k, l));
            }
          }
        }
      }
    }
  }
  return ans;
}

int solve(int W, int H, const vector<rect>& rects)
{
  vector<vector<bool> > grid(2*W+1, vector<bool>(2*H+1, true));
  for (int i = 0; i < 2*H+1; i++) {
    grid[0][i] = grid[2*W][i] = false;
    //printf("draw (w=0,h=%d) and (w=%d,h=%d)\n", i, 2*W, i);
  }
  for (int i = 0; i < 2*W+1; i++) {
    grid[i][0] = grid[i][2*H] = false;
  }

  for (vector<rect>::const_iterator it(rects.begin()); it != rects.end(); ++it) {
    for (int i = it->lower*2; i <= it->upper*2; i++) {
      grid[i][it->left*2] = grid[i][it->right*2] = false;
    }
    for (int i = it->left*2; i <= it->right*2; i++) {
      grid[it->lower*2][i] = grid[it->upper*2][i] = false;
    }
  }
  return bfs(grid);
}

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    int N;
    cin >> N;
    vector<rect> rects(N);
    for (int i = 0; i < N; i++) {
      int x1, y1, x2, y2;
      cin >> x1 >> y1 >> x2 >> y2;
      rects[i] = rect(x1, y1, x2, y2);
    }
    cout << solve(W, H, rects) << endl;
  }
  return 0;
}