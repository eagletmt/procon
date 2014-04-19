#include <iostream>
#include <vector>
#include <queue>
#include <cctype>
using namespace std;

struct state
{
  int f;
  int i, j;
  unsigned s;
  state() : f(0), i(-1), j(-1), s(0) {}
  state(int a, int b, int c, unsigned d) : f(a), i(b), j(c), s(d) {}
};

struct dungeon
{
  vector<string> grid;
  vector<vector<string> > moves;

  inline static int initial_floor(char c)
  {
    return c == '^' || isupper(c);
  }

  char get(const state& s) const
  {
    const char c = grid[s.i][s.j];
    if (c == '#' || c == '|') {
      return c;
    }
    int f = initial_floor(c);
    const int S = moves.size();
    for (int i = 0; i < S; i++) {
      const vector<string>& g = moves[i];
      if ((s.s & (1<<i)) && g[s.i][s.j] == '*') {
        f ^= 1;
      }
    }
    if (f == s.f) {
      return tolower(c);
    } else {
      return '#';
    }
  }
};

int main()
{
  int H, W;
  dungeon d;
  cin >> W >> H;
  d.grid.resize(H);
  state start;
  for (int i = 0; i < H; i++) {
    cin >> d.grid[i];
    for (int j = 0; j < W; j++) {
      if (d.grid[i][j] == '%') {
        start.i = i;
        start.j = j;
      }
    }
  }
  int S;
  cin >> S;
  for (int k = 0; k < S; k++) {
    vector<string> v(H);
    for (int i = 0; i < H; i++) {
      cin >> v[i];
    }
    d.moves.push_back(v);
  }

  static const int INF = 10000000;
  static int dist[2][50][50][1<<10];
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < H; j++) {
      for (int k = 0; k < W; k++) {
        fill_n(dist[i][j][k], 1<<S, INF);
      }
    }
  }
  dist[start.f][start.i][start.j][start.s] = 0;
  queue<state> q;
  q.push(start);
  while (!q.empty()) {
    const state s = q.front();
    q.pop();
    const int dd = dist[s.f][s.i][s.j][s.s] + 1;
    const char here = d.get(s);
    if (here == '&') {
      cout << dd-1 << endl;
      return 0;
    }

    for (int i = 0; i < 4; i++) {
      static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
      const state t(s.f, s.i + di[i], s.j + dj[i], s.s);
      int& next = dist[t.f][t.i][t.j][t.s];
      if (d.get(t) != '#' && dd < next) {
        next = dd;
        q.push(t);
      }
    }

    if (here == '|') {
      const state t(s.f ^ 1, s.i, s.j, s.s);
      int& next = dist[t.f][t.i][t.j][t.s];
      if (dd < next) {
        next = dd;
        q.push(t);
      }
    } else if (isalpha(here)) {
      const int sw = here - 'a';
      int f = s.f;
      if (d.moves[sw][s.i][s.j] == '*') {
        f ^= 1;
      }
      const state t(f, s.i, s.j, s.s ^ (1<<sw));
      int& next = dist[t.f][t.i][t.j][t.s];
      if (dd < next) {
        next = dd;
        q.push(t);
      }
    }
  }
  cout << -1 << endl;
  return 0;
}
