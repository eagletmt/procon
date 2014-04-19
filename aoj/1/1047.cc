#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
#include <complex>
using namespace std;
typedef complex<double> P;

static const double EPS = 1e-8;
static const double PI = acos(-1.0);

struct circle/*{{{*/
{
  P o;
  double r;
  circle() {}
  circle(const P& p, double x) : o(p), r(x) {}

  // POJ 1418 Viva Confetti
  // POJ 2149 Inherit the Spheres
  inline bool intersects(const circle& c) const
  {
    return !contains(c) && !c.contains(*this) && abs(o - c.o) <= r + c.r;
  }

  pair<P,P> intersection(const circle& c) const
  {
    // assert(intersects(c))
    const double d = abs(o - c.o);
    const double cos_ = (d*d + r*r - c.r*c.r) / (2*d);
    const double sin_ = sqrt(r*r - cos_*cos_);
    const P e = (c.o - o) / d;
    return make_pair(o + e*P(cos_, sin_), o + e*P(cos_, -sin_));
  }

  inline bool contains(const circle& c) const
  {
    return abs(o - c.o)+c.r <= r;
  }
};/*}}}*/

int main()
{
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<circle> cs;
    for (int i = 0; i < N; i++) {
      double x, y, r;
      scanf("%lf %lf %lf", &x, &y, &r);
      cs.push_back(circle(P(x, y), r));
    }

    for (vector<circle>::iterator it = cs.begin(); it != cs.end();) {
      bool contained = false;
      for (vector<circle>::const_iterator jt = cs.begin(); jt != cs.end(); ++jt) {
        if (it != jt && jt->contains(*it)) {
          contained = true;
          break;
        }
      }
      if (contained) {
        it = cs.erase(it);
      } else {
        ++it;
      }
    }

    N = cs.size();
    vector<vector<pair<double,double> > > spans(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (i == j) {
          continue;
        }
        const circle& c1 = cs[i];
        const circle& c2 = cs[j];
        if (c1.intersects(c2)) {
          const pair<P, P> r = c1.intersection(c2);
          if (abs(r.first - r.second) < EPS) {
            continue;
          }
          const pair<double, double> p = make_pair(arg(r.second - c1.o), arg(r.first - c1.o));
          if (p.first < p.second) {
            spans[i].push_back(p);
          } else {
            spans[i].push_back(make_pair(p.first, PI));
            spans[i].push_back(make_pair(-PI, p.second));
          }
        }
      }
    }

    double ans = 0;
    for (int i = 0; i < N; i++) {
      sort(spans[i].begin(), spans[i].end());
      for (vector<pair<double, double> >::iterator it = spans[i].begin(); it != spans[i].end() && it+1 != spans[i].end();) {
        pair<double, double>& p1 = *it;
        const pair<double, double>& p2 = *(it+1);
        if (p1.second > p2.first) {
          p1.second = max(p1.second, p2.second);
          spans[i].erase(it+1);
        } else {
          ++it;
        }
      }

      double ang = 2*PI;
      for (vector<pair<double, double> >::const_iterator it = spans[i].begin(); it != spans[i].end(); ++it) {
        ang -= (it->second - it->first);
      }
      ans += cs[i].r * ang;
    }
    printf("%.8f\n", ans);
  }
  return 0;
}
