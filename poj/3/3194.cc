#include <iostream>
#include <vector>
#include <queue>
using namespace std;

bool equidivision(const vector<vector<int> >& grid)
{
  const int N = grid.size();
  vector<vector<bool> > visited(N, vector<bool>(N, false));
  for (int n = 0; n < N; n++) {
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (grid[i][j] != n || visited[i][j]) {
          continue;
        }

        queue<pair<int,int> > q;
        q.push(make_pair(i, j));
        visited[i][j] = true;
        int c = 0;
        while (!q.empty()) {
          const pair<int,int> p = q.front();  q.pop();
          ++c;
          for (int d = 0; d < 4; d++) {
            static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
            const int k = p.first + di[d], l = p.second + dj[d];
            if (0 <= k && k < N && 0 <= l && l < N && grid[k][l] == n && !visited[k][l]) {
              q.push(make_pair(k, l));
              visited[k][l] = true;
            }
          }
        }
        if (c != N) {
          return false;
        }
      }
    }
  }
  return true;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > grid(N, vector<int>(N, N-1));
    for (int i = 0; i < N-1; i++) {
      for (int j = 0; j < N; j++) {
        int x, y;
        cin >> x >> y;
        --x;  --y;
        grid[x][y] = i;
      }
    }
    if (equidivision(grid)) {
      cout << "good" << endl;
    } else {
      cout << "wrong" << endl;
    }
  }
  return 0;
}