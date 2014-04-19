#include <cstdio>
#include <queue>
#include <algorithm>
using namespace std;

int H, W;
char grid[1000][1001];
int m[1000][1000];

bool ok(int t)
{
  static bool visited[1000][1000];
  for (int i = 0; i < H; i++) {
    fill_n(visited[i], W, false);
  }
  visited[0][0] = true;
  queue<pair<int,int> > q;
  q.push(make_pair(0, 0));
  while (!q.empty()) {
    const int x = q.front().first;
    const int y = q.front().second;
    q.pop();
    if (grid[x][y] == 't') {
      return true;
    }
    for (int d = 0; d < 4; d++) {
      static const int dx[] = {-1, 1, 0, 0}, dy[] = {0, 0, -1, 1};
      const int z = x + dx[d], w = y + dy[d];
      if (0 <= z && z < H && 0 <= w && w < W
          && !visited[z][w]
          && (grid[z][w] != '#' || m[z][w] <= t)) {
        visited[z][w] = true;
        q.push(make_pair(z, w));
      }
    }
  }
  return false;
}

int main()
{
  scanf("%d %d", &W, &H);
  for (int i = 0; i < H; i++) {
    scanf("%s", grid[i]);
  }
  int N;
  scanf("%d", &N);
  static const int INF = 10000000;
  for (int i = 0; i < H; i++) {
    fill_n(m[i], W, INF);
  }
  for (int i = 0; i < N; i++) {
    int x, y;
    scanf("%d %d", &x, &y);
    m[y][x] = i+1;
  }

  if (!ok(N)) {
    puts("-1");
    return 0;
  }

  int lo = 0, hi = N;
  while (lo < hi) {
    const int mid = (lo + hi)/2;
    if (ok(mid)) {
      hi = mid;
    } else {
      lo = mid+1;
    }
  }
  printf("%d\n", lo);
  return 0;
}
