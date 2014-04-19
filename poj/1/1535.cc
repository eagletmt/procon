#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    pair<int,int> house, church;
    cin >> house.first >> house.second >> church.first >> church.second;
    int L;
    cin >> L;
    set<pair<int,int> > closed;
    for (int i = 0; i < L; i++) {
      int x, y;
      cin >> x >> y;
      closed.insert(make_pair(x, y));
    }

    vector<vector<bool> > visited(N, vector<bool>(M, false));
    visited[house.first][house.second] = true;
    queue<pair<int,int> > q;
    q.push(house);
    while (!q.empty()) {
      const pair<int,int> p = q.front();
      q.pop();
      if (p == church) {
        cout << "YES" << endl;
        goto NEXT;
      }

      for (int d = 0; d < 4; d++) {
        static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
        const int i = p.first + di[d];
        const int j = p.second + dj[d];
        if (0 <= i && i < N && 0 <= j && j < M && !visited[i][j]) {
          const int k = church.first - (i - house.first);
          const int l = church.second - (j - house.second);
          if (0 <= k && k < N && 0 <= l && l < M && !closed.count(make_pair(i, j)) && !closed.count(make_pair(k, l))) {
            visited[i][j] = true;
            q.push(make_pair(i, j));
          }
        }
      }
    }
    cout << "NO" << endl;
NEXT:
    ;
  }
  return 0;
}