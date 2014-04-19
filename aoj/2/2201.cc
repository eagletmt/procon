#include <iostream>
#include <vector>
#include <complex>
#include <limits>
using namespace std;
typedef complex<double> P;
static const double PI = atan2(0.0, -0.0);
static const double EPS = 1e-6;

struct circle {
  P center;
  double radius, mag;
};

//Q86(x0,y0,r0)068Q86(x1,y1,r1)06EQ71ﾂ�AcA5}DA06EcA5pB9
void tangency(double x0, double y0, double r0, double x1, double y1, double r1, pair<P, P> out[4])
{
  const P v(x1 - x0, y1 - y0);
  const double a0 = arg(v);
  const double a1 = acos((r0 - r1) / abs(v));
  out[0] = make_pair(P(x0 + r0 * cos(a0 + a1), y0 + r0 * sin(a0 + a1)), P(x1 + r1 * cos(a0 + a1), y1 + r1 * sin(a0 + a1)));
  out[1] = make_pair(P(x0 + r0 * cos(a0 - a1), y0 + r0 * sin(a0 - a1)), P(x1 + r1 * cos(a0 - a1), y1 + r1 * sin(a0 - a1)));
  const double a2 = acos((r0 + r1) / abs(v));
  out[2] = make_pair(P(x0 + r0 * cos(a0 + a2), y0 + r0 * sin(a0 + a2)), P(x1 + r1 * cos(a0 + a2 + PI), y1 + r1 * sin(a0 + a2 + PI)));
  out[3] = make_pair(P(x0 + r0 * cos(a0 - a2), y0 + r0 * sin(a0 - a2)), P(x1 + r1 * cos(a0 - a2 + PI), y1 + r1 * sin(a0 - a2 + PI)));
}

double dot(const P& p, const P& q)
{
  return p.real()*q.real() + p.imag()*q.imag();
}

double norm2(const P& p)
{
  return dot(p, p);
}

P perpendicular_foot(const P& p, const pair<P,P>& line)
{
  const double t = dot(p - line.first, line.first - line.second) / norm2(line.first - line.second);
  return line.first + t*(line.first-line.second);
}

double distance_point_line(const P& p, const pair<P,P>& line)
{
  return abs(p - perpendicular_foot(p, line));
}


int count(const vector<circle>& cs, const pair<P,P>& line)
{
  int ans = 0;
  for (vector<circle>::const_iterator it(cs.begin()); it != cs.end(); ++it) {
    const double h = distance_point_line(it->center, line);
    if (it->radius - h <= EPS && h - (it->radius + it->mag) <= EPS) {
      ans++;
    }
  }
  return ans;
}

int solve(const vector<circle>& cs)
{
  const int N = cs.size();
  int ans = 1;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      const circle& c1 = cs[i];
      const circle& c2 = cs[j];
      pair<P,P> lines[4];

      tangency(c1.center.real(), c1.center.imag(), c1.radius, c2.center.real(), c2.center.imag(), c2.radius, lines);
      for (int k = 0; k < 4; k++) {
        ans = max(ans, count(cs, make_pair(lines[k].first, lines[k].second)));
      }
      tangency(c1.center.real(), c1.center.imag(), c1.radius + c1.mag, c2.center.real(), c2.center.imag(), c2.radius, lines);
      for (int k = 0; k < 4; k++) {
        ans = max(ans, count(cs, make_pair(lines[k].first, lines[k].second)));
      }
      tangency(c1.center.real(), c1.center.imag(), c1.radius, c2.center.real(), c2.center.imag(), c2.radius + c2.mag, lines);
      for (int k = 0; k < 4; k++) {
        ans = max(ans, count(cs, make_pair(lines[k].first, lines[k].second)));
      }
      tangency(c1.center.real(), c1.center.imag(), c1.radius+c1.mag, c2.center.real(), c2.center.imag(), c2.radius+c2.mag, lines);
      for (int k = 0; k < 4; k++) {
        ans = max(ans, count(cs, make_pair(lines[k].first, lines[k].second)));
      }
    }
  }
  return ans;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<circle> cs(N);
    for (int i = 0; i < N; i++) {
      cin >> cs[i].center.real() >> cs[i].center.imag() >> cs[i].radius >> cs[i].mag;
    }
    if (N == 1) {
      cout << 1 << endl;
    } else {
      cout << solve(cs) << endl;
    }
  }
  return 0;
}
