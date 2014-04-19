#include <cstdio>
#include <queue>
using namespace std;

typedef enum { STAND, VERT, HORIZ } Dir;
struct state
{
  int r, c;
  Dir dir;
  state() : r(-1), c(-1), dir(STAND) {}
  state(int a, int b, Dir d) : r(a), c(b), dir(d) {}
};

int R, C;
char stage[500][500];

int valid(int r, int c, Dir dir)
{
  if (0 <= r && r < R && 0 <= c && c < C) {
    switch (dir) {
      case STAND: return stage[r][c] != '#' && stage[r][c] != 'E';
      case VERT: return stage[r][c] != '#' && stage[r+1][c] != '#';
      case HORIZ: return stage[r][c] != '#' && stage[r][c+1] != '#';
    }
    return false;
  } else {
    return false;
  }
}

int bfs(const state& start)
{
  queue<pair<state, int> > q;
  q.push(make_pair(start, 0));

  static bool visited[500][500][3];
  for (int i = 0; i < R; i++) {
    for (int j = 0; j < C; j++) {
      for (int k = 0; k < 3; k++) {
        visited[i][j][k] = false;
      }
    }
  }
  visited[start.r][start.c][start.dir] = true;

  while (!q.empty()) {
    const pair<state, int> p = q.front();
    q.pop();
    const state s = p.first;
    const int d = p.second;
    if (s.dir == STAND && stage[s.r][s.c] == 'O') {
      return d;
    }

    for (int i = 0; i < 4; i++) {
      static const int dr[3][4] = {{-2, 0, 1, 0}, {-1, 0, 2, 0}, {-1, 0, 1, 0}};
      static const int dc[3][4] = {{0, 1, 0, -2}, {0, 1, 0, -1}, {0, 2, 0, -1}};
      static const Dir dd[3][4] = {{VERT, HORIZ, VERT, HORIZ}, {STAND, VERT, STAND, VERT}, {HORIZ, STAND, HORIZ, STAND}};
      const int r = s.r + dr[s.dir][i];
      const int c = s.c + dc[s.dir][i];
      const Dir dir = dd[s.dir][i];
      if (valid(r, c, dir) && !visited[r][c][dir]) {
        visited[r][c][dir] = true;
        q.push(make_pair(state(r, c, dir), d+1));
      }
    }
  }
  return -1;
}

int main()
{
  while (scanf("%d %d", &R, &C) == 2 && R != 0) {
    state start;
    for (int i = 0; i < R; i++) {
      scanf("%s", stage[i]);
      for (int j = 0; j < C; j++) {
        if (stage[i][j] == 'X') {
          stage[i][j] = '.';
          if (start.r != -1) {
            start.dir = j == start.c ? VERT : HORIZ;
          } else {
            start.r = i;
            start.c = j;
            start.dir = STAND;
          }
        }
      }
    }
    int ans = bfs(start);
    if (ans == -1) {
      puts("Impossible");
    } else {
      printf("%d\n", ans);
    }
  }
  return 0;
}