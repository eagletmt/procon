#include <cstdio>
#include <iostream>
#include <vector>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
static const double PI = acos(-1.0);

inline double cross(const P& a, const P& b)
{
  return a.real()*b.imag() - b.real()*a.imag();
}

inline double dot(const P& a, const P& b)
{
  return a.real()*b.real() + a.imag()*b.imag();
}

struct line
{
  P a, b;
  line() {}
  line(const P& x, const P& y) : a(x), b(y) {}
};

struct segment
{
  P a, b;
  segment(const P& x, const P& y) : a(x), b(y) {}
  inline bool intersects(const line& ln) const
  {
    return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS;
  }

  inline P intersection(const line& ln) const
  {
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline bool parallel(const line& ln) const
  {
    const double a = abs(arg(b - a) - arg(ln.b - ln.a));
    return a < EPS || abs(PI - a) < EPS;
  }
};

struct polygon
{
  vector<P> ps;
  polygon() {}
  polygon(const vector<P>& v) : ps(v) {}

  inline int size() const { return ps.size(); }
  inline void push_back(const P& p) { ps.push_back(p); }
  inline P& operator[](int i) { return ps[i]; }
  inline const P& operator[](int i) const { return ps[i]; }

  double area() const
  {
    // positive if polygon is clockwise
    double a = 0.0;
    const int N = ps.size();
    for (int i = 0; i < N; i++) {
      a += cross(ps[(i+1)%N], ps[i]);
    }
    return a/2.0;
  }

  polygon cut(const line& ln) const
  {
    const int N = ps.size();
    polygon ret;
    for (int i = 0; i < N; i++) {
      const segment seg(ps[i], ps[(i+1)%N]);
      if (cross(ln.b - ln.a, ps[i] - ln.a) < EPS) {
        ret.push_back(ps[i]);
        if (!seg.parallel(ln) && seg.intersects(ln)) {
          const P p = seg.intersection(ln);
          if (abs(p - ps[i]) > EPS) {
            ret.push_back(p);
          }
        }
      } else if (!seg.parallel(ln) && seg.intersects(ln)) {
        ret.push_back(seg.intersection(ln));
      }
    }
    return ret;
  }
};

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    polygon poly;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      poly.push_back(P(x, y));
    }

    polygon ans = poly;
    for (int i = 0; i < N; i++) {
      ans = ans.cut(line(poly[i], poly[(i+1)%N]));
    }
    printf("%.2f\n", ans.area());
  }
  return 0;
}