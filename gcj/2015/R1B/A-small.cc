#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int rev(int x)
{
  int y = 0;
  while (x > 0) {
    y = 10*y + (x % 10);
    x /= 10;
  }
  return y;
}

int solve(int N)
{
  vector<int> dist(N+1, -1);
  queue<int> q;
  dist[1] = 1;
  q.push(1);
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    const int d = dist[n];
    if (n == N) {
      return d;
    }

    if (dist[n+1] == -1) {
      dist[n+1] = d + 1;
      q.push(n+1);
    }
    const int m = rev(n);
    if (m <= N && dist[m] == -1) {
      dist[m] = d + 1;
      q.push(m);
    }
  }
  throw __LINE__;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;

    cout << "Case #" << Ti << ": " << solve(N) << endl;
  }
  return 0;
}
