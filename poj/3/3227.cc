#include <cstdio>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;
namespace std {
  bool operator<(const P& a, const P& b)
  {
    if (fabs(a.real() - b.real()) < EPS) {
      return a.imag() < b.imag();
    } else {
      return a.real() < b.real();
    }
  }
};

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }

  inline bool intersects(const line& ln) const
  {
    return !parallel(ln);
  }

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline double distance(const P& p) const
  {
    return abs(cross(p - a, b - a)) / abs(b - a);
  }

  inline P perpendicular(const P& p) const
  {
    // pB9 p 04B089vF4}DAN0A06BN0B08D05705FW82}DA06E�B3
    const double t = dot(p-a, a-b) / dot(b-a, b-a);
    return a + t*(a-b);
  }
};/*}}}*/

struct segment/*{{{*/
{
  P a, b;
  segment() {}
  segment(const P& x, const P& y) : a(x), b(y) {}

  inline bool intersects(const line& ln) const
  {
    return cross(ln.b - ln.a, a - ln.a) * cross(ln.b - ln.a, b - ln.a) < EPS;
  }

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }
};/*}}}*/

int main()
{
  int N, H;
  while (scanf("%d %d", &N, &H) != EOF && N != 0) {
    const P h(0, H);
    vector<P> ps;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      ps.push_back(P(x, y));
    }

    vector<segment> segs;
    for (int i = 0; i < N-1; i++) {
      segs.push_back(segment(ps[i], ps[i+1]));
    }

    vector<pair<P, bool> > v;
    P prev = ps[0];
    double ans = 0;
    for (int i = 1; i < N; i++) {
      line ln(h, ps[i]);
      for (int j = 0; j < i-1; j++) {
        if (segs[j].intersects(ln)) {
          prev = ps[i];
          goto NEXT;
        }
      }
      ans += abs(ps[i] - prev);
      if (i < N-1) {
        double c = cross(ps[i] - h, ps[i+1] - ps[i]);
        if (c > 0) {
          prev = ps[i];
          goto NEXT;
        } else {
          for (int j = i+1; j < N; j++) {
            if (segs[j].intersects(ln)) {
              prev = segs[j].intersection(ln);
              i = j;
              goto NEXT;
            }
          }
        }
      }
NEXT:
      ;
    }

    printf("%.2f\n", ans);
  }
  return 0;
}