#include <iostream>
#include <cstdio>
#include <vector>
#include <map>
#include <queue>
#include <complex>
#include <algorithm>
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
struct line
{
  P a, b;
  line() {}
  line(const P& p, const P& q) : a(p), b(q) {}
};

struct segment
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
    const P x = b - a;
    const P y = ln.b - ln.a;
    return a + x*(cross(y, ln.a - a))/cross(y, x);
  }

  inline bool parallel(const line& ln) const
  {
    return abs(cross(ln.b - ln.a, b - a)) < EPS;
  }
};
int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<P> ps;
    for (int i = 0; i < N; i++) {
      int x, y;
      cin >> x >> y;
      ps.push_back(P(x, y));
    }

    vector<P> qs(ps);
    for (int i = 0; i < N; i++) {
      const line ln(ps[i], ps[i] + P(1, 0));
      for (int j = 0; j < N-1; j++) {
        if (fabs(ps[i].imag() - ps[j].imag()) < EPS) {
          continue;
        }
        if (fabs(ps[i].imag() - ps[j+1].imag()) < EPS) {
          continue;
        }
        const segment s(ps[j], ps[j+1]);
        if (!s.parallel(ln) && s.intersects(ln)) {
          const P p = s.intersection(ln);
          qs.push_back(p);
        }
      }
    }
    sort(qs.begin(), qs.end());
    const int M = qs.size();

    map<int, double> dist;
    dist.insert(make_pair(M-1, 0.0));
    priority_queue<pair<double, int> > q;
    q.push(make_pair(0.0, M-1));
    while (!q.empty()) {
      const double c = -q.top().first;
      const int left = q.top().second/M;
      const int right = q.top().second%M;
      q.pop();
      if (left == right) {
        printf("%.3f\n", c);
        break;
      }
      if (dist[left*M+right] < c) {
        continue;
      }
      for (int dl = -1; dl <= 1; dl++) {
        for (int dr = -1; dr <= 1; dr++) {
          const int l = left + dl;
          const int r = right + dr;
          if (l < 0 || r >= M) {
            continue;
          }
          if (fabs(qs[l].imag() - qs[r].imag()) < EPS) {
            const double cc = c + abs(qs[l] - qs[left]) + abs(qs[r] - qs[right]);
            const int p = l*M + r;
            map<int,double>::iterator it = dist.find(p);
            if (it == dist.end()) {
              dist.insert(make_pair(p, cc));
              q.push(make_pair(-cc, p));
            } else if (cc+EPS < it->second) {
              it->second = cc;
              q.push(make_pair(-cc, p));
            }
          }
        }
      }
    }
  }
  return 0;
}
