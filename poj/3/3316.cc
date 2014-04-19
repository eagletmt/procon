#include <iostream>
#include <vector>
#include <queue>
using namespace std;

static const int di[] = {-1, 1, 0, 0};
static const int dj[] = {0, 0, -1, 1};

bool can_put_here(const vector<vector<bool> >& grid, int first, int second, int i, int j)
{
  const int N = grid.size();
  const int M = grid[0].size();
  for (int d = 0; d < 4; d++) {
    const int k = i + di[d];
    const int l = j + dj[d];
    if (0 <= k && k < N && 0 <=l && l < M
        && !(k == first && l == second)
        && grid[k][l]) {
      return false;
    }
  }
  return true;
}

int solve(const vector<vector<bool> >& grid)
{
  const int N = grid.size();
  const int M = grid[0].size();
  vector<vector<bool> > visited(N, vector<bool>(M, false));
  vector<vector<pair<int,int> > > corners;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!grid[i][j] || visited[i][j]) {
        continue;
      }
      vector<pair<int,int> > corner;
      queue<pair<int,int> > q;
      q.push(make_pair(i, j));
      visited[i][j] = true;
      while (!q.empty()) {
        const pair<int,int> p = q.front();
        q.pop();
        int c = 0;
        for (int d = 0; d < 4; d++) {
          const int next_i = p.first + di[d];
          const int next_j = p.second + dj[d];
          if (0 <= next_i && next_i < N
              && 0 <= next_j && next_j < M
              && grid[next_i][next_j]) {
            c++;
            if (!visited[next_i][next_j]) {
              visited[next_i][next_j] = true;
              q.push(make_pair(next_i, next_j));
            }
          }
        }
        if (c < 2) {
          corner.push_back(make_pair(p.first, p.second));
        }
      }
      corners.push_back(corner);
    }
  }

  int ans = 0;
  for (vector<vector<pair<int,int> > >::const_iterator it(corners.begin()); it != corners.end(); ++it) {
    for (vector<pair<int,int> >::const_iterator jt(it->begin()); jt != it->end(); ++jt) {
      for (int d = 0; d < 4; d++) {
        const int i = jt->first + di[d];
        const int j = jt->second + dj[d];
        if (0 <= i && i < N && 0 <= j && j < M && !grid[i][j]) {
          if (can_put_here(grid, jt->first, jt->second, i, j)) {
            goto NEXT;
          }
        }
      }
    }
    ++ans;
NEXT:
    ;
  }
  return ans;
}

int main()
{
  int n, m;
  while (cin >> n >> m && n != 0) {
    vector<vector<bool> > grid(n, vector<bool>(m));
    for (int i = 0; i < n; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < m; j++) {
        grid[i][j] = s[j] == '1';
      }
    }
    cout << solve(grid) << endl;
  }
  return 0;
}