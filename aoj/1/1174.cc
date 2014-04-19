#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int H, W;

vector<pair<int,int> > bfs(const int grid[8][8])
{
  int dist[8][8];
  for (int i = 0; i < H; i++) {
    fill_n(dist[i], W, 0);
  }
  dist[0][0] = true;
  queue<pair<int,int> > q;
  q.push(make_pair(0, 0));
  const int color = grid[0][0];
  vector<pair<int,int> > ans;
  while (!q.empty()) {
    ans.push_back(q.front());
    const int i = q.front().first, j = q.front().second;
    q.pop();
    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const int k = i + di[d], l = j + dj[d];
      if (0 <= k && k < H && 0 <= l && l < W && grid[k][l] == color && !dist[k][l]) {
        dist[k][l] = true;
        q.push(make_pair(k, l));
      }
    }
  }
  return ans;
}

int dfs(const int grid[8][8], int depth, int C)
{
  const vector<pair<int,int> > c = bfs(grid);
  if (depth == 0) {
    if (grid[0][0] == C) {
      return c.size();
    } else {
      return 0;
    }
  } else {
    int ans = 0;
    for (int i = 1; i <= 6; i++) {
      int g[8][8];
      for (int j = 0; j < H; j++) {
        copy(grid[j], grid[j]+W, g[j]);
      }
      for (vector<pair<int,int> >::const_iterator it = c.begin(); it != c.end(); ++it) {
        g[it->first][it->second] = i;
      }
      ans = max(ans, dfs(g, depth-1, C));
    }
    return ans;
  }
}

int main()
{
  int C;
  while (cin >> H >> W >> C && H != 0) {
    int grid[8][8];
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cin >> grid[i][j];
      }
    }
    cout << dfs(grid, 5, C) << endl;
  }
  return 0;
}
