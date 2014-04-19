#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int D;
  while (scanf("%d", &D) == 1 && D != 0) {
    int dp[2] = {100000, 0};
    for (int i = 0; i < D; i++) {
      double r;
      scanf("%lf", &r);
      const int canada = max(dp[0], static_cast<int>(dp[1] * 0.97 * r));
      const int us = max(dp[1], static_cast<int>(dp[0] * 0.97 / r));
      dp[0] = canada;
      dp[1] = us;
    }
    printf("%.2f\n", dp[0]/100.0);
  }
  return 0;
}