#include <iostream>
#include <vector>
#include <queue>
#include <complex>
using namespace std;
typedef complex<int> P;

struct State {
  P pos;
  int dir;
  int depth;
  State(P pos, int dir, int depth) : pos(pos), dir(dir), depth(depth) {}
};

int main()
{
  int M, N;
  while (cin >> M >> N && M != 0) {
    vector<vector<bool> > block(M, vector<bool>(N));
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < N; j++) {
        int x;
        cin >> x;
        block[i][j] = x == 1;
      }
    }
    string dir;
    P start, goal;
    cin >> start.real() >> start.imag() >> goal.real() >> goal.imag() >> dir;
    int d;
    if (dir == "north") {
      d = 0;
    } else if (dir == "west") {
      d = 1;
    } else if (dir == "south") {
      d = 2;
    } else {
      d = 3;
    }

    vector<vector<vector<bool> > > visited(M+1, vector<vector<bool> >(N+1, vector<bool>(4, false)));
    queue<State> q;
    q.push(State(start, d, 0));
    visited[start.real()][start.imag()][d] = true;
    while (!q.empty() && q.front().pos != goal) {
      State s = q.front();
      q.pop();
      for (int g = 1; g <= 3; g++) {
        static const int d_m[] = {-1, 0, 1, 0};
        static const int d_n[] = {0, -1, 0, 1};
        int m = s.pos.real() + d_m[s.dir]*g;
        int n = s.pos.imag() + d_n[s.dir]*g;
        if (m > 0 && m < M && n > 0 && n < N && !visited[m][n][s.dir]) {
          if (block[m-1][n] || block[m][n-1] || block[m][n] || block[m-1][n-1])
            break;

          visited[m][n][s.dir] = true;
          q.push(State(P(m, n), s.dir, s.depth+1));
        }
      }
      if (!visited[s.pos.real()][s.pos.imag()][(s.dir+1)%4]) {
        q.push(State(s.pos, (s.dir+1)%4, s.depth+1));
        visited[s.pos.real()][s.pos.imag()][(s.dir+1)%4] = true;
      }
      if (!visited[s.pos.real()][s.pos.imag()][(s.dir+3)%4]) {
        q.push(State(s.pos, (s.dir+3)%4, s.depth+1));
        visited[s.pos.real()][s.pos.imag()][(s.dir+3)%4] = true;
      }
    }
    if (q.empty()) {
      cout << -1 << endl;
    } else {
      cout << q.front().depth << endl;
    }
  }
  return 0;
}
