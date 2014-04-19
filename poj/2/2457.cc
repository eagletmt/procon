#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N, K;
  scanf("%d %d", &N, &K);
  vector<vector<int> > g(K);
  for (int i = 0; i < N; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a;  --b;
    g[a].push_back(b);
  }
  queue<int> q;
  vector<int> prev(K, -1);
  prev[0] = 0;
  q.push(0);
  while (!q.empty()) {
    const int n = q.front();
    q.pop();
    if (n == K-1) {
      vector<int> ans;
      for (int k = n; k != 0; k = prev[k]) {
        ans.push_back(k+1);
      }
      ans.push_back(1);
      printf("%zu\n", ans.size());
      for (vector<int>::const_reverse_iterator it = ans.rbegin(); it != ans.rend(); ++it) {
        printf("%d\n", *it);
      }
      return 0;
    }

    for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      if (prev[*it] == -1) {
        prev[*it] = n;
        q.push(*it);
      }
    }
  }
  puts("-1");
  return 0;
}
