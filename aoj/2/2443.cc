#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
using namespace std;

int N;

long long encode(const int *a)
{
  long long n = 0;
  for (int i = 0; i < N; i++) {
    n = 10*n + a[i];
  }
  return n;
}

void decode(int *a, long long n)
{
  for (int i = 0; i < N; i++) {
    a[N-i-1] = n % 10;
    n /= 10;
  }
}

void bfs(map<long long, int>& dist, long long start)
{
  queue<pair<long long, int> > q;
  dist[start] = 0;
  q.push(make_pair(start, 0));
  while (!q.empty()) {
    int a[10];
    decode(a, q.front().first);
    const int d = q.front().second;
    q.pop();
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        int b[10];
        copy(a, a+N, b);
        reverse(b+i, b+j+1);
        const long long n = encode(b);
        const map<long long, int>::const_iterator it = dist.find(n);
        if (it == dist.end()) {
          dist.insert(make_pair(n, d+1));
          if (d+1 < 4) {
            q.push(make_pair(n, d+1));
          }
        }
      }
    }
  }
}

int main()
{
  cin >> N;
  int a[10], b[10];
  for (int i = 0; i < N; i++) {
    cin >> a[i];
    --a[i];
    b[i] = i;
  }
  map<long long, int> m1, m2;
  bfs(m1, encode(a));
  bfs(m2, encode(b));
  int ans = 9;
  for (map<long long, int>::const_iterator it = m1.begin(); it != m1.end(); ++it) {
    map<long long, int>::const_iterator jt = m2.find(it->first);
    if (jt != m2.end()) {
      ans = min(ans, it->second + jt->second);
    }
  }
  cout << ans << endl;
  return 0;
}
