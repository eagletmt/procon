#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<int> > g(N*N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        int x, y;
        cin >> x >> y;
        g[i*N+j].push_back(y*N+x);
        g[y*N+x].push_back(i*N+j);
      }
    }
    vector<bool> visited(N*N, false);
    int ans = 0;
    for (int i = 0; i < N*N; i++) {
      if (!visited[i]) {
        visited[i] = true;
        queue<int> q;
        q.push(i);
        ++ans;
        while (!q.empty()) {
          const int n = q.front();
          q.pop();
          for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
            if (!visited[*it]) {
              visited[*it] = true;
              q.push(*it);
            }
          }
        }
      }
    }
    cout << ans << endl;
  }
  return 0;
}
