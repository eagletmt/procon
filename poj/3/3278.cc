#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  static const int L = 100000;
  int N, K;
  cin >> N >> K;
  vector<bool> visited(L+1, false);
  queue<pair<int,int> > q;
  q.push(make_pair(0, N));
  visited[N] = true;
  while (!q.empty()) {
    const pair<int,int> p = q.front();
    q.pop();
    const int& x = p.second;
    const int& d = p.first;
    if (x == K) {
      cout << d << endl;
      break;
    }

    if (x > 0 && !visited[x-1]) {
      q.push(make_pair(d+1, x-1));
      visited[x-1] = true;
    }
    if (x < L && !visited[x+1]) {
      q.push(make_pair(d+1, x+1));
      visited[x+1] = true;
    }
    if (2*x <= L && !visited[2*x]) {
      q.push(make_pair(d+1, 2*x));
      visited[2*x] = true;
    }
  }
  return 0;
}