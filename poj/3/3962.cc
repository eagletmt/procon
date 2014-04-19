#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;
static const double PI = acos(-1.0);

struct P3 { double x, y, z; };

double f(const vector<P3>& v, double theta, double& r, double &h)
{
  r = h = 0;
  for (vector<P3>::const_iterator it = v.begin(); it != v.end(); ++it) {
    const double xy = sqrt(it->x * it->x + it->y * it->y);
    const double t = tan(theta);
    r = max(r, xy + it->z/t);
    h = max(h, it->z + xy*t);
  }
  return PI*r*r*h/3.0;
}

int main()
{
  int N;
  scanf("%d", &N);
  vector<P3> v(N);
  for (int i = 0; i < N; i++) {
    scanf("%lf %lf %lf", &v[i].x, &v[i].y, &v[i].z);
  }

  double left = 0.0, right = PI/2.0;
  for (int i = 0; i < 100; i++) {
    const double x1 = (2*left + right)/3.0;
    const double x2 = (left + 2*right)/3.0;
    double r1, h1, r2, h2;
    if (f(v, x1, r1, h1) < f(v, x2, r2, h2)) {
      right = x2;
    } else {
      left = x1;
    }
  }
  double r, h;
  f(v, (left+right)/2.0, r, h);
  printf("%.3f %.3f\n", h, r);
  return 0;
}