#include <iostream>
#include <vector>
#include <queue>
#include <complex>
#include <cmath>
using namespace std;
typedef complex<int> P;

inline double sqr(double x) { return x*x; }
inline double dist(const P& x, const P& y)
{
  return sqrt(sqr(x.real() - y.real()) + sqr(x.imag() - y.imag()));
}

int main()
{
  const double WALK = 10.0 * 1000 / 60;
  const double SUBWAY = 40.0 * 1000 / 60;

  P start, goal;
  cin >> start.real() >> start.imag() >> goal.real() >> goal.imag();
  vector<P> points;
  points.push_back(start);
  points.push_back(goal);
  vector<pair<int,int> > lines;
  for (P p; cin >> p.real() >> p.imag(); ) {
    const int beg = points.size();
    points.push_back(p);
    while (cin >> p.real() >> p.imag() && !(p.real() == -1 && p.imag() == -1)) {
      points.push_back(p);
    }
    lines.push_back(make_pair(beg, points.size()));
  }

  const int N = points.size();
  vector<vector<pair<int,double> > > g(N);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      if (i != j) {
        g[i].push_back(make_pair(j, dist(points[i], points[j]) / WALK));
      }
    }
  }
  for (vector<pair<int,int> >::const_iterator it = lines.begin(); it != lines.end(); ++it) {
    for (int i = it->first; i+1 != it->second; i++) {
      const double t = dist(points[i], points[i+1]) / SUBWAY;
      g[i].push_back(make_pair(i+1, t));
      g[i+1].push_back(make_pair(i, t));
    }
  }

  priority_queue<pair<double,int> > q;
  q.push(make_pair(0, 0));
  vector<double> cost(N, 1e10);
  cost[0] = 0;
  while (!q.empty()) {
    const double c = -q.top().first;
    const double n = q.top().second;
    q.pop();
    if (n == 1) {
      cout << lround(c) << endl;
      break;
    }
    if (c > cost[n]) {
      continue;
    }
    for (vector<pair<int,double> >::const_iterator it = g[n].begin(); it != g[n].end(); ++it) {
      const double m = it->first;
      const double cc = c + it->second;
      if (cc < cost[m]) {
        cost[m] = cc;
        q.push(make_pair(-cc, m));
      }
    }
  }
  return 0;
}
