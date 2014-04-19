#include <iostream>
#include <vector>
using namespace std;

bool dfs(vector<pair<int,int> >& path, int step, int x, int y, int p, int q, vector<vector<bool> >& visited)
{
  static const int dx[] = {-2, -2, -1, -1, +1, +1, +2, +2};
  static const int dy[] = {-1, +1, -2, +2, -2, +2, -1, +1};

  path[step].first = x;
  path[step].second = y;
  ++step;
  if (step == p*q) {
    return true;
  } else {
    visited[x][y] = true;
    for (int i = 0; i < 8; i++) {
      const int next_x = x + dx[i];
      const int next_y = y + dy[i];
      if (next_x >= 0 && next_y >= 0
          && next_x < q && next_y < p
          && !visited[next_x][next_y]) {
        if (dfs(path, step, next_x, next_y, p, q, visited)) {
          return true;
        }
      }
    }
    visited[x][y] = false;
    return false;
  }
}

int main(void)
{
  int N;
  cin >> N;

  for (int i = 0; i < N; i++) {
    int p, q;
    cin >> p >> q;

    vector<vector<bool> > visited(q, vector<bool>(p, false));
    cout << "Scenario #" << i+1 << ':' << endl;
    vector<pair<int,int> > path(p*q);
    if (dfs(path, 0, 0, 0, p, q, visited)) {
      for (int c = 0; c < p*q; c++) {
        cout << char(path[c].first+'A') << path[c].second+1;
      }
      cout << endl;
    } else {
      cout << "impossible" <<endl;
    }
    cout << endl;
  }

  return 0;
}
