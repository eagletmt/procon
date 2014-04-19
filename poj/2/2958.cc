#include <cstdio>
#include <algorithm>
#include <limits>
using namespace std;

int main()
{
  int N;
  scanf("%d", &N);
  while (N-- > 0) {
    int x, y;
    scanf("%d %d", &x, &y);
    static int sum_x[100], sum_y[100];
    fill_n(sum_x, x, 0);
    fill_n(sum_y, y, 0);
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        int a;
        scanf("%d", &a);
        sum_x[j] += a;
        sum_y[i] += a;
      }
    }
    static int d[100][100];
    for (int i = 0; i < y; i++) {
      fill_n(d[i], x, 0ULL);
    }
    for (int i = 0; i < y; i++) {
      for (int j = 0; j < x; j++) {
        for (int k = 0; k < y; k++) {
          d[i][j] += sum_y[k] * abs(i - k);
        }
        for (int l = 0; l < x; l++) {
          d[i][j] += sum_x[l] * abs(j - l);
        }
      }
    }
    int ans = numeric_limits<int>::max();
    for (int i = 0; i < y; i++) {
      ans = min(ans, *min_element(d[i], d[i]+x));
    }
    printf("%d blocks\n", ans);
  }
  return 0;
}