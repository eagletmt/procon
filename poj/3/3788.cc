#include <cstdio>
#include <vector>
#include <complex>
#include <algorithm>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}
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

  // AOJ 1171 Laser Beam Relections
  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};/*}}}*/

struct horizontal
{
  int y, x1, x2;
  horizontal(int a, int b, int c) : y(a), x1(b), x2(c) {}
};

bool member(const vector<P>& v, const P& p)
{
  for (vector<P>::const_iterator it = v.begin(); it != v.end(); ++it) {
    if (abs(*it - p) < EPS) {
      return true;
    }
  }
  return false;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int Ti, N;
    scanf("%d %d", &Ti, &N);
    vector<P> poly;
    static const int INF = 10000000;
    int ymax = -INF, ymin = INF;
    for (int i = 0; i < N; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      poly.push_back(P(x, y));
      ymax = max(ymax, y);
      ymin = min(ymin, y);
    }

    vector<horizontal> ans;
    for (int y = ymax; y >= ymin; y--) {
      const line ln(P(0, y), P(1, y));
      vector<P> v;
      for (int i = 0; i < N; i++) {
        const segment seg(poly[i], poly[(i+1)%N]);
        if (seg.intersects(ln)) {
          const P p = seg.intersection(ln);
          if (!member(v, p)) {
            v.push_back(p);
          }
        }
      }
      if (v.size() == 2) {
        if (v[0].real() > v[1].real()) {
          swap(v[0], v[1]);
        }
        int x1 = ceil(v[0].real());
        if (member(v, P(x1, y))) {
          ++x1;
        }
        int x2 = floor(v[1].real());
        if (member(v, P(x2, y))) {
          --x2;
        }
        if (x1 <= x2) {
          ans.push_back(horizontal(y, x1, x2));
        }
      }
    }

    printf("%d %d\n", Ti, int(ans.size()));
    for (vector<horizontal>::const_iterator it = ans.begin(); it != ans.end(); ++it) {
      printf("%d %d %d\n", it->y, it->x1, it->x2);
    }
  }
}