#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int X, Y, N;
  cin >> X >> Y >> N;
  bool puddle[1001][1001];
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    puddle[a+500][b+500] = true;
  }
  const pair<int,int> goal(X+500, Y+500);

  vector<vector<bool> > visited(1001, vector<bool>(1001, false));
  queue<pair<int, pair<int,int> > > q;
  q.push(make_pair(0, make_pair(500, 500)));
  visited[500][500] = true;
  while (!q.empty()) {
    const pair<int, pair<int,int> > p = q.front();
    q.pop();
    if (p.second == goal) {
      cout << p.first << endl;
      break;
    }

    for (int d = 0; d < 4; d++) {
      static const int di[] = {-1, 1, 0, 0};
      static const int dj[] = {0, 0, -1, 1};
      const int i = p.second.first + di[d];
      const int j = p.second.second + dj[d];
      if (0 <= i && i <= 1000 && 0 <= j && j <= 1000 && !puddle[i][j] && !visited[i][j]) {
        visited[i][j] = true;
        q.push(make_pair(p.first+1, make_pair(i, j)));
      }
    }
  }
  return 0;
}