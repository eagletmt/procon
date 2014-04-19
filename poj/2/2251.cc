#include <iostream>
#include <queue>
using namespace std;

struct P {
  int i, j, k, m;
  P() : m(0) {}
  P(int a, int b, int c, int m = 0) : i(a), j(b), k(c), m(m) {}
};

int main()
{
  int L, R, C;
  while (cin >> L >> R >> C && !(L == 0 && R == 0 && C == 0)) {
    char maze[30][30][30];
    P start;
    for (int i = 0; i < L; i++) {
      for (int j = 0; j < R; j++) {
        for (int k = 0; k < C; k++) {
          cin >> maze[i][j][k];
          if (maze[i][j][k] == 'S') {
            start = P(i, j, k);
          }
        }
      }
    }

    queue<P> q;
    q.push(start);
    maze[start.i][start.j][start.k] = '#';
    while (!q.empty()) {
      const P p = q.front();
      q.pop();
      static const int dir_i[] = {1, 0, 0, -1, 0, 0};
      static const int dir_j[] = {0, 1, 0, 0, -1, 0};
      static const int dir_k[] = {0, 0, 1, 0, 0, -1};
      for (int d = 0; d < 6; d++) {
        const int i = p.i + dir_i[d];
        const int j = p.j + dir_j[d];
        const int k = p.k + dir_k[d];
        if (0 <= i && i < L && 0 <= j && j < R && 0 <= k && k < C && maze[i][j][k] != '#') {
          if (maze[i][j][k] == 'E') {
            cout << "Escaped in " << p.m+1 << " minute(s)." << endl;
            goto ESCAPED;
          }
          q.push(P(i, j, k, p.m+1));
          maze[i][j][k] = '#';
        }
      }
    }
    cout << "Trapped!" << endl;
ESCAPED:
    ;
  }
  return 0;
}
