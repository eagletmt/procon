#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int main()
{
  const double PI = atan2(+0.0, -0.0);
  int w, h;
  while (scanf("%d %d", &w, &h) != EOF && w != 0) {
    if (w > h) {
      swap(w, h);
    }
    // w <= h
    const double r1 = min(h/3.0, w/(2.0*PI));
    const double r2 = min(w/2.0, h/(2.0*(PI+1.0)));
    const double v = max(r1*r1*PI*(h-2*r1), r2*r2*PI*w);
    printf("%.3f\n", v);
  }
  return 0;
}