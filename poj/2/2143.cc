#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

bool ok(int x, int y, int z, int N)
{
  return 0 <= x && x < N && 0 <= y && y < N && 0 <= z && z < N;
}

bool finish(const vector<vector<vector<int> > >& c, int M, int me)
{
  const int N = c.size();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        for (int d = 0; d < 13; d++) {
          int x = i, y = j, z = k;
          int m = 0;
          while (ok(x, y, z, N)) {
            if (c[x][y][z] == me) {
              ++m;
            } else {
              m = 0;
            }
            if (m >= M) {
              return true;
            }
            static const int di[] = {0,1,1, 1,0,1,1, 1, 0,-1,-1,-1,0};
            static const int dj[] = {1,1,0,-1,1,1,0,-1,-1,-1, 0, 1,0};
            static const int dk[] = {0,0,0, 0,1,1,1, 1, 1, 1, 1, 1,1};
            x += di[d];
            y += dj[d];
            z += dk[d];
          }
        }
      }
    }
  }
  return false;
}

int main()
{
  int N, M, P;
  while (cin >> N >> M >> P && N != 0) {
    vector<pair<int,int> > xy(P);
    for (int i = 0; i < P; i++) {
      cin >> xy[i].first >> xy[i].second;
      --xy[i].first;
      --xy[i].second;
    }

    vector<vector<vector<int> > > cube(N, vector<vector<int> >(N, vector<int>(N, -1)));
    for (int i = 0; i < P; i++) {
      vector<int>& v = cube[xy[i].first][xy[i].second];
      for (int j = 0; j < N; j++) {
        if (v[j] == -1) {
          v[j] = i&1;
          break;
        }
      }
      if (finish(cube, M, i&1)) {
        cout << (i&1 ? "White" : "Black") << ' ' << i+1 << endl;
        goto NEXT;
      }
    }
    cout << "Draw" << endl;
NEXT:
    ;
  }
  return 0;
}