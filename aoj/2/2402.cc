#include <cstdio>
#include <vector>
#include <queue>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-8;
static const double PI = acos(-1.0);

inline double dot(const P& a, const P& b) { return a.real()*b.real() + a.imag()*b.imag(); }
inline double cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int ccw(const P& a, P b, P c)
{
  b -= a;
  c -= a;
  if (cross(b, c) > EPS) {
    return +1;
  } else if (cross(b, c) < -EPS) {
    return -1;
  } else if (dot(b, c) < -EPS) {
    return +2;
  } else if (dot(b, b) + EPS < dot(c, c)) {
    return -2;
  } else {
    return 0;
  }
}

struct segment
{
  P a, b;
  segment() {}
  segment(const P& p, const P& q) : a(p), b(q) {}

  inline bool intersects(const segment& seg) const
  {
    return
      ccw(a, b, seg.a) * ccw(a, b, seg.b) <= 0
      && ccw(seg.a, seg.b, a) * ccw(seg.a, seg.b, b) <= 0;
  }

  inline double distance(const P& p) const
  {
    if (dot(b-a, p-a) < EPS) {
      return abs(p-a);
    } else if (dot(a-b, p-b) < EPS) {
      return abs(p-b);
    } else {
      return abs(cross(b-a, p-a))/abs(b-a);
    }
  }

  inline double distance(const segment& seg) const
  {
    if (intersects(seg)) {
      return 0;
    } else {
      return
        min(
            min(distance(seg.a), distance(seg.b)),
            min(seg.distance(a), seg.distance(b)));
    }
  }
};

struct star
{
  segment segs[5];
  star(double x, double y, double a, double r) {
    const P o(x, y);
    P p(0, r);
    p *= polar(1.0, a/180.0*PI);
    const P m = polar(1.0, 72.0/180.0*PI);
    P ps[5];
    for (int i = 0; i < 5; i++) {
      ps[i] = o + p;
      p *= m;
    }
    for (int i = 0, j = 0; i < 5; i++) {
      segs[i] = segment(ps[j], ps[(j+2) % 5]);
      j = (j+2) % 5;
    }
  }

  double distance(const star& s) const
  {
    double ans = 1e10;
    for (int i = 0; i < 5; i++) {
      for (int j = 0; j < 5; j++) {
        ans = min(ans, segs[i].distance(s.segs[j]));
      }
    }
    return ans;
  }
};

int main()
{
  int N, M, L;
  while (scanf("%d %d %d", &N, &M, &L) != EOF && N != 0) {
    --M; --L;
    vector<star> stars;
    for (int i = 0; i < N; i++) {
      int x, y, a, r;
      scanf("%d %d %d %d", &x, &y, &a, &r);
      stars.push_back(star(x, y, a, r));
    }

    vector<vector<double> > g(N, vector<double>(N));
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        double d = stars[i].distance(stars[j]);
        g[i][j] = g[j][i] = d;
      }
    }
    priority_queue<pair<double,int> > q;
    vector<double> dist(N, 1e10);
    dist[M] = 0;
    q.push(make_pair(0.0, M));
    while (!q.empty()) {
      const double d = -q.top().first;
      const int n = q.top().second;
      q.pop();
      if (n == L) {
        printf("%.20f\n", fabs(d));
        break;
      }
      for (int i = 0; i < N; i++) {
        if (n == i) {
          continue;
        }
        const double dd = d + g[n][i];
        if (dd < dist[i]) {
          dist[i] = dd;
          q.push(make_pair(-dd, i));
        }
      }
    }
  }
  return 0;
}
