#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct state {
  int i, j;
  int hp;
  int time;
  state(int a, int b, int c, int d = 0) : i(a), j(b), hp(c), time(d) {}
  bool operator<(const state& rhs) const
  {
    return time > rhs.time;
  }
};

int main()
{
  int w, h;
  while (cin >> w >> h && w != 0) {
    priority_queue<state> q;
    vector<vector<int> > grid(h, vector<int>(w));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> grid[i][j];
        if (grid[i][j] == 2) {
          grid[i][j] = 1;
          q.push(state(i, j, 6));
        }
      }
    }

    vector<vector<vector<int> > > dist(h, vector<vector<int> >(w, vector<int>(6, 1000000)));
    dist[q.top().i][q.top().j][5] = 0;
    while (!q.empty()) {
      state s = q.top();
      q.pop();
      if (grid[s.i][s.j] == 3) {
        cout << s.time << endl;
        goto NEXT;
      }
      if (grid[s.i][s.j] == 4) {
        s.hp = 6;
      }
      if (s.hp == 1) {
        continue;
      }

      for (int d = 0; d < 4; d++) {
        static const int dir_i[] = {-1, 1, 0, 0};
        static const int dir_j[] = {0, 0, -1, 1};
        const int next_i = s.i + dir_i[d];
        const int next_j = s.j + dir_j[d];
        if (0 <= next_i && next_i < h && 0 <= next_j && next_j < w && grid[next_i][next_j] != 0
            && s.time+1 < dist[next_i][next_j][s.hp-1-1]) {
          q.push(state(next_i, next_j, s.hp-1, s.time+1));
          dist[next_i][next_j][s.hp-1-1] = s.time+1;
        }
      }
    }
    cout << -1 << endl;
NEXT:;
  }
  return 0;
}
