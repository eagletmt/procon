#include <iostream>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<double> P;

static const double EPS = 1e-6;

namespace std {/*{{{*/
  bool operator<(const P& p, const P& q)
  {
    return abs(p.real() - q.real()) < EPS ? p.imag() < q.imag() : p.real() < q.real();
  }
};/*}}}*/

double dot(const P& p, const P& q) { return p.real()*q.real() + p.imag()*q.imag(); }

double cross(const P& a, const P& b) { return imag(conj(a) * b); }

int ccw(P a, P b, P c) {/*{{{*/
  b -= a; c -= a;
  if (cross(b, c) > 0) {
    return 1; // counter clockwise
  } else if (cross(b, c) < 0) {
    return -1;  // clockwise
  } else if (dot(b, c) < 0) {
    return 2; // c-a-b on line
  } else if (abs(b) < abs(c)) {
    return -2;  // a-b-c on line
  }
  return 0;
}/*}}}*/

vector<P> convex(vector<P> ps)/* QF8S05 {{{*/
{
  sort(ps.begin(), ps.end());
  const int N = ps.size();
  vector<P> ch(2*N);
  int k = 0;
  // upper
  for (int i = 0; i < N; i++) {
    while (k >= 2 && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  // lower
  for (int i = N-2, t = k+1; i >= 0; i--) {
    while (k >= t && ccw(ch[k-2], ch[k-1], ps[i]) <= 0) {
      k--;
    }
    ch[k] = ps[i];
    k++;
  }
  ch.resize(k-1);
  return ch;
}/*}}}*/

double area2(const vector<P>& v)/*{{{*/
{
  double a = 0.0;
  const int N = v.size();
  for (int i = 0; i < N; i++) {
    a += cross(v[i], v[(i+1)%N]);
  }
  return abs(a)/2.0;
}/*}}}*/

int main()
{
  int N;
  cin >> N;
  vector<P> ps(N);
  for (int i = 0; i < N; i++) {
    cin >> ps[i].real() >> ps[i].imag();
  }
  vector<P> h = convex(ps);
  double s = area2(h);
  cout << int(s/50) << endl;
  return 0;
}