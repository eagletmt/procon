#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main()
{
  int x, h;
  while (cin >> x >> h && !(x == 0 && h == 0)) {
    const double l = hypot(h, x/2.0);
    const double s = 2*x*l + x*x;
    printf("%.6f\n", s);
  }
  return 0;
}
