#include <cstdio>
using namespace std;

int main()
{
  long long S, x, y, dx, dy;
  while (scanf("%lld%lld%lld%lld%lld", &S, &x, &y, &dx, &dy) == 5 && S != 0) {
    static bool visited[1001][1001];
    for (int i = 0; i <= S; i++) {
      for (int j = 0; j <= S; j++) {
        visited[i][j] = false;
      }
    }
    int ans = 0;
    while (true) {
      long long a = x%S, b = y%S;
      const long long c = x/S, d = y/S;
      if (a > 0 && b > 0 && c%2 != d%2) {
        printf("After %d jumps the flea lands at (%lld, %lld).\n", ans, x, y);
        break;
      }
      if (c%2 != d%2) {
        if (a == 0) { a = S; }
        if (b == 0) { b = S; }
      }
      if (visited[a][b]) {
        puts("The flea cannot escape from black squares.");
        break;
      }
      visited[a][b] = true;
      x += dx;  y += dy;
      ++ans;
    }
  }
  return 0;
}