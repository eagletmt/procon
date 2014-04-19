#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int A, B;
    scanf("%d %d", &A, &B);
    double p = 1.0;
    double ans = 1 + B + 1; // enter right away
    for (int i = 1; i <= A; i++) {
      double q;
      scanf("%lf", &q);
      p *= q;
      const double ok = p * (A-i + B-i + 1);
      const double ng =  (1.0-p) * (A-i + B-i + 1 + B + 1);
      ans = min(ans, ok + ng);
    }
    printf("Case #%d: %.6f\n", Ti, ans);
  }
  return 0;
}
