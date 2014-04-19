#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<vector<int> > grid(2*H+1, vector<int>(2*W+1, 0));
    for (int i = 0; i < 2*H+1; i++) {
      grid[i][0] = grid[i][2*W] = 1;
    }
    for (int j = 0; j < 2*W+1; j++) {
      grid[0][j] = grid[2*H][j] = 1;
    }
    grid[0][1] = 0;
    grid[2*H][2*W-1] = 0;

    for (int j = 1; j < W; j++) {
      cin >> grid[1][2*j];
      if (grid[1][2*j]) {
        grid[2][2*j] = 1;
      }
    }
    for (int i = 1; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cin >> grid[2*i][2*j+1];
        if (grid[2*i][2*j+1]) {
          grid[2*i][2*j] = grid[2*i][2*j+2] = 1;
        }
      }
      for (int j = 1; j < W; j++) {
        cin >> grid[2*i+1][2*j];
        if (grid[2*i+1][2*j]) {
          grid[2*i][2*j] = grid[2*i+2][2*j] = 1;
        }
      }
    }

    queue<pair<int,int> > q;
    q.push(make_pair(0, 1));
    vector<vector<int> > dist(2*H+1, vector<int>(2*W+1, 1000000));
    dist[0][1] = 0;
    const pair<int,int> goal(2*H, 2*W-1);
    while (!q.empty()) {
      const pair<int,int> p = q.front();
      q.pop();
      const int c = dist[p.first][p.second];
      if (p == goal) {
        cout << c/2 << endl;
        goto NEXT;
      }
      for (int d = 0; d < 4; d++) {
        static const int di[] = {-1, 1, 0, 0};
        static const int dj[] = {0, 0, -1, 1};
        const int i = p.first + di[d];
        const int j = p.second + dj[d];
        if (i >= 0 && j >= 0 && !grid[i][j] && c+1 < dist[i][j]) {
          dist[i][j] = c+1;
          q.push(make_pair(i, j));
        }
      }
    }
    cout << 0 << endl;
NEXT:
    ;
  }
  return 0;
}
