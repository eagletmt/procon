#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int R, C, D;
    cin >> R >> C >> D;
    vector<vector<int> > grid(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
      string line;
      cin >> line;
      for (int j = 0; j < C; j++) {
        grid[i][j] = line[j]-'0'+D;
      }
    }
    int K = min(R, C);
    for (; K >= 3; K--) {
      for (int i = 0; i <= R-K; i++) {
        for (int j = 0; j <= C-K; j++) {
          double sx = 0.0, sy = 0.0;
          for (int k = 0; k < K; k++) {
            for (int l = 0; l < K; l++) {
              if ((k == 0 && l == 0) || (k == K-1 && l == 0) || (k == 0 && l == K-1) || (k == K-1 && l == K-1)) {
              } else {
                sx += grid[i+k][j+l] * (k - (K-1)/2.0);
                sy += grid[i+k][j+l] * (l - (K-1)/2.0);
              }
            }
          }
          if (abs(sx) < 1e-6 && abs(sy) < 1e-6) {
            goto DONE;
          }
        }
      }
    }
DONE:
    cout << "Case #" << Ti << ": ";
    if (K < 3) {
      cout << "IMPOSSIBLE" << endl;
    } else {
      cout << K << endl;
    }
  }
  return 0;
}
