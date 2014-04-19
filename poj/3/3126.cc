#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  static const int N = 10000;
  vector<bool> sieve(N, false);
  for (int i = 2; i < N; i++) {
    if (!sieve[i]) {
      for (int j = i+i; j < N; j += i) {
        sieve[j] = true;
      }
    }
  }

  int T;
  cin >> T;
  while (T-- > 0) {
    int start, goal;
    cin >> start >> goal;
    vector<bool> visited(N, false);
    visited[start] = true;
    queue<pair<int,int> > q;
    q.push(make_pair(start, 0));

    while (!q.empty()) {
      const pair<int,int> p = q.front();
      q.pop();

      if (p.first == goal) {
        cout << p.second << endl;
        break;
      }

      for (int i = 0; i < 10; i++) {
        const int n = (p.first/10)*10 + i;
        if (!visited[n] && !sieve[n]) {
          visited[n] = true;
          q.push(make_pair(n, p.second + 1));
        }
      }
      for (int i = 0; i < 10; i++) {
        const int n = (p.first/100)*100 + i*10 + p.first%10;
        if (!visited[n] && !sieve[n]) {
          visited[n] = true;
          q.push(make_pair(n, p.second + 1));
        }
      }
      for (int i = 0; i < 10; i++) {
        const int n = (p.first/1000)*1000 + i*100 + p.first%100;
        if (!visited[n] && !sieve[n]) {
          visited[n] = true;
          q.push(make_pair(n, p.second + 1));
        }
      }
      for (int i = 1; i < 10; i++) {
        const int n = i*1000 + p.first%1000;
        if (!visited[n] && !sieve[n]) {
          visited[n] = true;
          q.push(make_pair(n, p.second + 1));
        }
      }
    }
  }
  return 0;
}
