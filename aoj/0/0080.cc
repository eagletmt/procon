#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
  int q;
  while (scanf("%d", &q) == 1 && q != -1) {
    double x = q/2.0;
    for (;;) {
      x = x - (x*x*x - q)/(3*x*x);
      if (fabs(x*x*x - q) < 1e-5*q) {
        break;
      }
    }
    printf("%.6f\n", x);
  }
  return 0;
}
