#include <iostream>
#include <vector>
using namespace std;

pair<int,int> match(const vector<vector<int> >& scenery, int x, int y, const vector<vector<int> >& picture)
{
  const int M = picture.size();
  pair<int,int> ans = make_pair(1000, 1000);

  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (picture[i][j] != -1 && picture[i][j] != scenery[x+i][y+j]) {
        goto L1;
      }
      if (picture[i][j] != -1 && x+i < ans.first) {
        ans.first = x+i;
        ans.second = min(ans.second, y+j);
      }
    }
  }
  return ans;
L1:
  ans = make_pair(1000, 1000);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (picture[j][M-i-1] != -1 && picture[j][M-i-1] != scenery[x+i][y+j]) {
        goto L2;
      }
      if (picture[j][M-i-1] != -1 && x+i < ans.first) {
        ans.first = x+i;
        ans.second = min(ans.second, y+j);
      }
    }
  }
  return ans;
L2:
  ans = make_pair(1000, 1000);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (picture[M-i-1][M-j-1] != -1 && picture[M-i-1][M-j-1] != scenery[x+i][y+j]) {
        goto L3;
      }
      if (picture[M-i-1][M-j-1] != -1 && x+i < ans.first) {
        ans.first = x+i;
        ans.second = min(ans.second, y+j);
      }
    }
  }
  return ans;
L3:
  ans = make_pair(1000, 1000);
  for (int i = 0; i < M; i++) {
    for (int j = 0; j < M; j++) {
      if (picture[M-j-1][i] != -1 && picture[M-j-1][i] != scenery[x+i][y+j]) {
        return make_pair(-1, -1);
      }
      if (picture[M-j-1][i] != -1 && x+i < ans.first) {
        ans.first = x+i;
        ans.second = min(ans.second, y+j);
      }
    }
  }
  return ans;
}

pair<int,int> solve(const vector<vector<int> >& scenery, const vector<vector<int> >& picture)
{
  const int N = scenery.size();
  const int M = picture.size();
  for (int i = 0; i <= N-M; i++) {
    for (int j = 0; j <= N-M; j++) {
      const pair<int,int> p = match(scenery, i, j, picture);
      if (p.first >= 0) {
        return p;
      }
    }
  }
  return make_pair(-1, -1);
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<vector<int> > scenery(N, vector<int>(N));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        cin >> scenery[i][j];
      }
    }
    vector<vector<int> > picture(M, vector<int>(M));
    for (int i = 0; i < M; i++) {
      for (int j = 0; j < M; j++) {
        cin >> picture[i][j];
      }
    }

    const pair<int,int> ans = solve(scenery, picture);
    if (ans.first == -1) {
      cout << "NA" << endl;
    } else {
      cout << ans.second+1 << ' ' << ans.first+1 << endl;
    }
  }
  return 0;
}
