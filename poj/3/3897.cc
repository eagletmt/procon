#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

double f(const vector<string>& grid, const pair<int,int>& start, double L)
{
  const int H = grid.size(), W = grid[0].size();
  vector<vector<double> > dist(H, vector<double>(W, 1e10));
  priority_queue<pair<double, pair<int,int> > > q;
  q.push(make_pair(0, start));
  dist[start.first][start.second] = 0;
  while (!q.empty()) {
    const double d = -q.top().first;
    const pair<int,int> p = q.top().second;
    q.pop();
    if (grid[p.first][p.second] == 'E') {
      return d;
    }
    if (dist[p.first][p.second] < d) {
      continue;
    }

    for (int k = 0; k < 4; k++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const int i = p.first + di[k], j = p.second + dj[k];
      if (0 <= i && i < H && 0 <= j && j < W && grid[i][j] != '#') {
        const double dd = d + (di[k] == 0 ? 1 : L);
        if (dd < dist[i][j]) {
          dist[i][j] = dd;
          q.push(make_pair(-dd, make_pair(i, j)));
        }
      }
    }
  }
  return 1e10;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    double L;
    int N;
    cin >> L >> N;
    vector<string> grid(N);
    cin.ignore();
    pair<int,int> start(-1, -1);
    for (int i = 0; i < N; i++) {
      getline(cin, grid[i]);
      const int W = grid[i].size();
      for (int j = 0; j < W; j++) {
        if (grid[i][j] == 'S') {
          grid[i][j] = ' ';
          start.first = i;
          start.second = j;
        }
      }
    }

    double lo = 0.0, hi = 1000;
    for (int i = 0; i < 50; i++) {
      const double mid = (lo + hi)/2.0;
      const double len = f(grid, start, mid);
      if (len < L) {
        lo = mid;
      } else {
        hi = mid;
      }
    }
    printf("Case #%d: %.3f%%\n", Ti, (lo+hi)/2.0 * 100.0);
  }
  return 0;
}