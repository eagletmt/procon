#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct state
{
  int d, n, k;
  state(int a, int b, int c)
    : d(a), n(b), k(c)
  {}
  bool operator<(const state& s) const
  {
    return d > s.d;
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<pair<int,int> > balloons(N+1);
    balloons[0] = make_pair(0, 0);
    for (int i = 1; i <= N; i++) {
      cin >> balloons[i].first >> balloons[i].second;
    }

    static const int INF = 10000000;
    vector<vector<int> > dist(N+1, vector<int>(4, INF));
    priority_queue<state> q;
    q.push(state(0, 0, 0));
    dist[0][0] = 0;
    int ans = 0;
    while (!q.empty()) {
      const int d = q.top().d;
      const int n = q.top().n;
      const int k = q.top().k;
      q.pop();
      ans = max(ans, n);
      const int t = balloons[n].second;
      if (n == N) {
        cout << "OK " << d+balloons[n].first << endl;
        goto NEXT;
      }

      if (k < 3) {
        // go to (n+1)-th balloon directly
        const int dd = abs(balloons[n+1].first - balloons[n].first);
        const int tt = dd * (k+1);
        if (t+tt <= balloons[n+1].second && d+dd < dist[n+1][k+1]) {
          dist[n+1][k+1] = d+dd;
          q.push(state(d+dd, n+1, k+1));
        }
      }
      // go home and go to (n+1)-th balloon
      const int dd = balloons[n].first + balloons[n+1].first;
      const int tt = balloons[n].first*(k+1) + balloons[n+1].first;
      if (t+tt <= balloons[n+1].second && d+dd < dist[n+1][1]) {
        dist[n+1][1] = d+dd;
        q.push(state(d+dd, n+1, 1));
      }
    }
    cout << "NG " << ans+1 << endl;
NEXT:
    ;
  }
  return 0;
}
