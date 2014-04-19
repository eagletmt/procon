#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
static const int INF = 10000000;

int encode(const int *a)
{
  int n = 0;
  for (int i = 0; i < 8; i++) {
    n = n*8 + a[i];
  }
  return n;
}

void decode(int *a, int n)
{
  for (int i = 0; i < 8; i++) {
    a[7-i] = n%8;
    n /= 8;
  }
}

int main()
{
  int N;
  cin >> N;
  int c[8][8] = {{0}};
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> c[i][j];
    }
  }

  int init;
  {
    int a[8] = {0};
    for (int i = 0; i < N; i++) {
      a[i] = i;
    }
    init = encode(a);
  }
  map<int,int> dist;
  dist[init] = 0;
  priority_queue<pair<int,int> > q;
  q.push(make_pair(0, init));
  while (!q.empty()) {
    const int cost = -q.top().first;
    const int n = q.top().second;
    q.pop();
    if (dist[n] < cost) {
      continue;
    }
    int a[8];
    decode(a, n);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        swap(a[i], a[j]);
        const int cc = cost + c[i][j];
        const int m = encode(a);
        map<int,int>::iterator it = dist.find(m);
        if (it == dist.end() || cc < it->second) {
          dist[m] = cc;
          q.push(make_pair(-cc, m));
        }
        swap(a[i], a[j]);
      }
    }
  }
  int ans = 0;
  for (map<int,int>::const_iterator it = dist.begin(); it != dist.end(); ++it) {
    ans = max(ans, it->second);
  }
  cout << ans << endl;
  return 0;
}
