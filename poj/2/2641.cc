#include <cstdio>
#include <cmath>
using namespace std;
static const double PI = acos(-1.0);

int main()
{
  int a, b, s, m, n;
  while (scanf("%d %d %d %d %d", &a, &b, &s, &m, &n) && s > 0) {
    printf("%.2f %.2f\n", atan2(n*b, m*a)/PI*180, sqrt(double(m)*m*a*a + double(n)*n*b*b)/s);
  }
  return 0;
}