#include <cstdio>
#include <cmath>
using namespace std;
static const double PI = acos(-1.0);

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    if (Ti != 1) {
      putchar('\n');
    }
    int a, b, c, d;
    scanf("%d %d %d %d", &a, &b, &c, &d);
    double M = a, N = b, L = c, C = d;
    printf("Case %d:\n", Ti);
    double s = L*L*M*N/100.0;
    double p1 = (L-C)*(L-C)*(N-2)*(M-2) + (L-C/2.0)*(L-C)*2*(N+M-4) + (L-C/2.0)*(L-C/2.0)*4;
    double p2 = (L-C/2.0)*C*2*(N-1 + M-1) + (L-C)*C*((N-2)*(M-1) + (M-2)*(N-1));
    double p4 = PI*(C/2.0)*(C/2.0)*(N-1)*(M-1);
    double p3 = C*C*(N-1)*(M-1) - p4;
    printf("Probability of covering 1 tile  = %.04f%%\n", fabs(p1/s));
    printf("Probability of covering 2 tiles = %.04f%%\n", fabs(p2/s));
    printf("Probability of covering 3 tiles = %.04f%%\n", fabs(p3/s));
    printf("Probability of covering 4 tiles = %.04f%%\n", fabs(p4/s));
  }
  return 0;
}
