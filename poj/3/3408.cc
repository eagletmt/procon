#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  static vector<int> g[1000];
  for (int i = 0; i < N; i++) {
    int c;
    scanf("%d", &c);
    for (int j = 0; j < c; j++) {
      int x;
      scanf("%d", &x);
      --x;
      g[i].push_back(x);
    }
  }

  int ans = 0, first = -1;
  for (int i = 0; i < N; i++) {
    queue<pair<int,int> > q;
    q.push(make_pair(0, i));
    static bool visited[1000];
    fill_n(visited, N, false);
    visited[i] = true;
    int m = 0, c = 0;
    while (!q.empty()) {
      const int n = q.front().second;
      const int d = q.front().first;
      q.pop();
      m = d;
      ++c;
      for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (!visited[*it]) {
          visited[*it] = true;
          q.push(make_pair(d+1, *it));
        }
      }
    }
    if (c == N && m >= ans) {
      ans = m;
      first = i+1;
    }
  }
  if (first == -1) {
    puts("impossible");
  } else {
    printf("%d\n%d\n", ans, first);
  }
  return 0;
}