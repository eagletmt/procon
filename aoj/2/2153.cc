#include <iostream>
#include <vector>
#include <queue>
#include <complex>
using namespace std;
typedef complex<int> P;

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<string> roomL(H), roomR(H);
    P startL, startR;
    for (int i = 0; i < H; i++) {
      cin >> roomL[i] >> roomR[i];
      for (int j = 0; j < W; j++) {
        if (roomL[i][j] == 'L') {
          roomL[i][j] = '.';
          startL = P(i, j);
        }
        if (roomR[i][j] == 'R') {
          roomR[i][j] = '.';
          startR = P(i, j);
        }
      }
    }

    queue<pair<P,P> > q;
    q.push(make_pair(startL, startR));
    vector<vector<bool> > visited(W*H, vector<bool>(W*H, false));
    visited[startL.real()*W + startL.imag()][startR.real()*W + startR.imag()] = true;
    while (!q.empty()) {
      const pair<P, P> p = q.front();
      q.pop();
      if (roomL[p.first.real()][p.first.imag()] == '%'
          || roomR[p.second.real()][p.second.imag()] == '%') {
        if (roomL[p.first.real()][p.first.imag()] == '%'
            && roomR[p.second.real()][p.second.imag()] == '%') {
          cout << "Yes" << endl;
          goto NEXT;
        } else {
          continue;
        }
      }

      for (int d = 0; d < 4; d++) {
        static const P dir[] = {P(-1,0), P(1,0), P(0,-1), P(0,1)};
        P nextL = p.first + dir[d];
        P nextR = p.second + P(dir[d].real(), dir[d].imag() == -1 ? 1 : (dir[d].imag() == 1 ? -1 : 0));
        if (nextL.real() == -1 || nextL.real() == H
            || nextL.imag() == -1 || nextL.imag() == W
            || roomL[nextL.real()][nextL.imag()] == '#') {
          nextL = p.first;
        }
        if (nextR.real() == -1 || nextR.real() == H
            || nextR.imag() == -1 || nextR.imag() == W
            || roomR[nextR.real()][nextR.imag()] == '#') {
          nextR = p.second;
        }
        if (!visited[nextL.real()*W + nextL.imag()][nextR.real()*W + nextR.imag()]) {
          q.push(make_pair(nextL, nextR));
          visited[nextL.real()*W + nextL.imag()][nextR.real()*W + nextR.imag()] = true;
        }
      }
    }
    cout << "No" << endl;
NEXT:
    ;
  }
  return 0;
}
