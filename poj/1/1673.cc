#include <iostream>
#include <vector>
#include <complex>
#include <cstdio>

#define M_PI_2 1.570796326795

using namespace std;
const double EPS = 1e-8;
typedef complex<double> P;
struct L : public vector<P> {
  L(const P& a, const P& b)
  {
    push_back(a);
    push_back(b);
  }
};

double cross(const P& a, const P& b) {
  return imag(conj(a)*b);
}

P crosspoint(const L &l, const L &m) {
  double A = cross(l[1] - l[0], m[1] - m[0]);
  double B = cross(l[1] - l[0], l[1] - m[0]);
  if (abs(A) < EPS && abs(B) < EPS) return m[0]; // same line
  return m[0] + B / A * (m[1] - m[0]);
}

P solve(P a, P b, P c)
{
  b -= a;
  c -= a;

  P d = c * P(0, -1);
  P e = b * P(0, 1);
  P f = b + e;
  P g = b + (b-c) * P(0, -1);
  P h = (d + e) * 0.5;
  P i = b + ((f - b) + (g - b))*0.5;

  P o = crosspoint(L(P(0,0), h), L(b, i));
  return a + o;
}

int main(void)
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    double a, b, c, d, e, f;
    cin >> a >> b >> c >> d >> e >> f;
    P p = solve(P(a,b), P(c,d), P(e,f));
    printf("%.4f %.4f\n", real(p), imag(p));
  }
  return 0;
}

