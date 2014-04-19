#include <iostream>
#include <cstdio>
#include <complex>
using namespace std;
typedef complex<double> P;

static const double PI = atan2(0.0, -0.0);

double cross(const P& a, const P& b) { return imag(conj(a) * b); }

P intersection_line_line(const pair<P,P>& l1, const pair<P,P>& l2)
{
  const P a = l1.second - l1.first;
  const P b = l2.second - l2.first;
  return l1.first + a*(cross(b, l2.first-l1.first)/cross(b, a));
}

double solve(const P& a, const P& b, const P& c)
{
  const P m = (a+b)/2.0;
  const P n = (b+c)/2.0;
  const P x = m + (b-a)*P(0,1);
  const P y = n + (c-b)*P(0,1);
  const P o = intersection_line_line(make_pair(m, x), make_pair(n, y));
  const double r = abs(o - a);
  return 2*r*PI;
}

int main()
{
  P a, b, c;
  while (cin >> a.real() >> a.imag() >> b.real() >> b.imag() >> c.real() >> c.imag()) {
    printf("%.2f\n", solve(a, b, c));
  }
  return 0;
}