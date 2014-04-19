#include <iostream>
#include <vector>
using namespace std;

struct P {
  int i, j;
  P() {}
  P(int i, int j) : i(i), j(j) {}
  bool operator==(const P& p) const
  {
    return i == p.i && j == p.j;
  }
};

int main()
{
  static const int N = 13;

  P start, end, lines_start[3], lines_end[3];
  while (cin >> start.j >> start.i
             >> end.j >> end.i
             >> lines_start[0].j >> lines_start[0].i >> lines_end[0].j >> lines_end[0].i
             >> lines_start[1].j >> lines_start[1].i >> lines_end[1].j >> lines_end[1].i
             >> lines_start[2].j >> lines_start[2].i >> lines_end[2].j >> lines_end[2].i) {

    start.i = 2*start.i - 1; start.j = 2*start.j - 1;
    end.i = 2*end.i - 1; end.j = 2*end.j - 1;
    for (int k = 0; k < 3; k++) {
      lines_start[k].i = 2*lines_start[k].i; lines_start[k].j = 2*lines_start[k].j;
      lines_end[k].i = 2*lines_end[k].i; lines_end[k].j = 2*lines_end[k].j;
    }

    vector<vector<char> > grid(N, vector<char>(N, ' '));
    for (int i = 0; i < N; i++) {
      grid[i][0] = grid[i][N-1] = 'X';
      grid[0][i] = grid[N-1][i] = 'X';
    }

    for (int k = 0; k < 3; k++) {
      for (int i = lines_start[k].i; i <= lines_end[k].i; i++) {
        grid[i][lines_start[k].j] = 'X';
      }
      for (int j = lines_start[k].j; j <= lines_end[k].j; j++) {
        grid[lines_start[k].i][j] = 'X';
      }
    }

    grid[start.i][start.j] = '#';
    vector<P> cur(1, start);
    while (!cur.empty()) {
      vector<P> next;
      for (vector<P>::const_iterator it(cur.begin()); it != cur.end(); ++it) {
        const P& p = *it;
        if (p == end) {
          next.clear();
          break;
        }
        static const int dir_i[] = {-1, 1, 0, 0};
        static const int dir_j[] = {0, 0, -1, 1};
        static const char dir[] = "NSWE";
        for (int d = 0; d < 4; d++) {
          P q(p.i + dir_i[d], p.j + dir_j[d]);
          if (grid[q.i][q.j] == ' ') {
            grid[q.i][q.j] = 'V';
            q.i += dir_i[d];
            q.j += dir_j[d];
            grid[q.i][q.j] = dir[d];
            next.push_back(q);
          }
        }
      }
      cur = next;
    }

    string route = "";
    for (P p = end; !(p == start); ) {
      route = grid[p.i][p.j] + route;
      switch (grid[p.i][p.j]) {
        case 'N':
          p.i += 2; break;
        case 'S':
          p.i -= 2; break;
        case 'W':
          p.j += 2; break;
        case 'E':
          p.j -= 2; break;
      }
    }
    cout << route << endl;
  }
  return 0;
}
