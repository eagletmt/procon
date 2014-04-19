#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
static const double EPS = 1e-8;
typedef complex<double> P;

int main()
{
  double H, V, h, v;
  for (int Ti = 1; scanf("%lf %lf %lf %lf", &H, &V, &h, &v) != EOF && fabs(v) > EPS; Ti++) {
    int N;
    scanf("%d", &N);
    printf("Case %d:\n", Ti);
    for (int i = 0; i < N; i++) {
      double x, y;
      scanf("%lf %lf", &x, &y);

      bool black = true;
      for (double hh = H, vv = V;; black = !black) {
        double a = hh * h;
        double b = vv * v;
        if (x < a && y < b) {
          // lower-left
          hh *= h;
          vv *= v;
        } else if (a < x && b < y) {
          // upper-right
          hh *= 1-h;
          vv *= 1-v;
          x -= a;
          y -= b;
        } else {
          puts(black ? "black" : "white");
          break;
        }
      }
    }
  }
  return 0;
}
