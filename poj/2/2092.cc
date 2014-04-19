#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  int players[10001];
  while (scanf("%d %d", &N, &M), N != 0) {
    int n = 0;
    fill(players, players+10001, 0);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < M; j++) {
        int x;
        scanf("%d", &x);
        ++players[x];
        n = max(n, x);
      }
    }
    ++n;

    const int m = *max_element(players, players+n);
    int m2 = 0;
    for (int i = 0; i < n; i++) {
      if (players[i] != m) {
        m2 = max(m2, players[i]);
      }
    }
    for (int i = 0; i < n; i++) {
      if (players[i] == m2) {
        printf("%d ", i);
      }
    }
    puts("");
  }
  return 0;
}