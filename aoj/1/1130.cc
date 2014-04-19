#include <iostream>
#include <vector>
#include <queue>
using namespace std;
typedef pair<int,int> P;

int main()
{
  int w, h;
  while (cin >> w >> h && w != 0) {
    vector<string> grid(h);
    P start;
    for (int i = 0; i < h; i++) {
      cin >> grid[i];
      for (int j = 0; j < w; j++) {
        if (grid[i][j] == '@') {
          start = make_pair(i, j);
          grid[i][j] = '#';
        }
      }
    }

    queue<P> q;
    q.push(start);
    int ans = 0;
    while (!q.empty()) {
      const P p = q.front();
      q.pop();

      ans++;
      for (int d = 0; d < 4; d++) {
        static const int dir_h[] = {-1, 1, 0, 0};
        static const int dir_w[] = {0, 0, -1, 1};
        const int next_h = p.first+dir_h[d];
        const int next_w = p.second+dir_w[d];
        if (next_h >= 0 && next_h < h && next_w >= 0 && next_w < w
            && grid[next_h][next_w] == '.') {
          q.push(make_pair(next_h, next_w));
          grid[next_h][next_w] = '#';
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
