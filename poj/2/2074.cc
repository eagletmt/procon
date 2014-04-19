#include <cstdio>
#include <queue>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-6;

enum event_type {
  BEGIN,
  END,
  INC,
  DEC,
};

struct event
{
  double x;
  event_type type;
  event(double a, event_type b) : x(a), type(b) {}
  bool operator<(const event& e) const { return x > e.x; }
};

inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }
struct line/*{{{*/
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}

  inline P intersection(const line& ln) const
  {
    // assert(intersects(ln))
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }
};/*}}}*/

int main()
{
  double x1, x2, y;
  while (scanf("%lf %lf %lf", &x1, &x2, &y) != EOF && !(fabs(x1) < EPS && fabs(x1) < EPS && fabs(y) < EPS)) {
    const P hl(x1, y), hr(x2, y);
    scanf("%lf %lf %lf", &x1, &x2, &y);
    const P pl(x1, y), pr(x2, y);
    const line prop(pl, pr);
    int N;
    scanf("%d", &N);
    priority_queue<event> q;
    q.push(event(pl.real(), BEGIN));
    q.push(event(pr.real(), END));
    for (int i = 0; i < N; i++) {
      scanf("%lf %lf %lf", &x1, &x2, &y);
      if (pr.imag() < y && y < hr.imag()) {
        const P left(x1, y), right(x2, y);
        const line inc(hr, left), dec(hl, right);
        q.push(event(prop.intersection(inc).real(), INC));
        q.push(event(prop.intersection(dec).real(), DEC));
      }
    }

    double ans = 0.0;
    int obs = 0;
    bool in = false;
    double prev = -1e10;
    while (!q.empty()) {
      const event evt = q.top();
      q.pop();
      if (obs == 0 && in) {
        ans = max(ans, evt.x - prev);
      }
      switch (evt.type) {
        case BEGIN:
          in = true;
          break;
        case END:
          in = false;
          break;
        case INC:
          ++obs;
          break;
        case DEC:
          if (obs == 0) {
            throw "dec";
          }
          --obs;
          break;
      }
      prev = evt.x;
    }
    if (fabs(ans) < EPS) {
      puts("No View");
    } else {
      printf("%.2f\n", ans);
    }
  }
  return 0;
}