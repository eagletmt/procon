#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  scanf("%d %d", &N, &M);
  static vector<int> g[1000];
  for (int i = 0; i < M; i++) {
    int u, v;
    scanf("%d %d", &u, &v);
    --u;  --v;
    g[u].push_back(v);
  }

  int c = 0;
  static bool visited[1000];
  for (int i = 0; i < N; i++) {
    fill_n(visited, N, false);
    queue<int> q;
    q.push(i);
    visited[i] = true;
    while (!q.empty()) {
      const int n = q.front();
      q.pop();
      for (vector<int>::const_iterator it(g[n].begin()); it != g[n].end(); ++it) {
        if (!visited[*it]) {
          visited[*it] = true;
          ++c;
          q.push(*it);
        }
      }
    }
  }
  printf("%d\n", N*(N-1)/2 - c);
  return 0;
}