#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

vector<int> g[10000];

bool visited[10000];
bool covered[10000];
bool tower[10000];
int ans;

void dfs(int n, int p)
{
  visited[n] = true;
  for (vector<int>::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
    if (!visited[*it]) {
      if (tower[n]) {
        covered[*it] = true;
      }
      dfs(*it, n);
      if (tower[*it]) {
        covered[n] = true;
      }
    }
  }
  if (!covered[n]) {
    ++ans;
    tower[p] = true;
    covered[p] = true;
    covered[n] = true;
  }
}

int main()
{
  int N;
  scanf("%d", &N);
  for (int i = 0; i < N-1; i++) {
    int a, b;
    scanf("%d %d", &a, &b);
    --a;  --b;
    g[a].push_back(b);
    g[b].push_back(a);
  }
  dfs(0, 0);
  printf("%d\n", ans);
  return 0;
}