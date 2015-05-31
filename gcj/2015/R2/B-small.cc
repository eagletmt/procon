#include <iostream>
#include <vector>
#include <cstdio>
#include <cmath>
using namespace std;
static const double EPS = 1e-8;

struct impossible {};

double solve(int N, double V, double X, const vector<pair<double,double> >& v)
{
  if (N == 1) {
    if (fabs(X - v[0].second) < EPS) {
      return V / v[0].first;
    } else {
      throw impossible();
    }
  } else if (N == 2) {
    if (fabs(v[0].second - v[1].second) < EPS) {
      if (fabs(X - v[0].second) < EPS) {
        return V / (v[0].first + v[1].first);
      } else {
        throw impossible();
      }
    } else {
      double t1 = (V*(v[1].second - X)) / (v[0].first * (v[1].second - v[0].second));
      double t2 = (V*(v[0].second - X)) / (v[1].first * (v[0].second - v[1].second));
      if (t1 < -EPS || t2 < -EPS) {
        throw impossible();
      } else {
        return max(t1, t2);
      }
    }
  } else {
    throw __LINE__;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    double V, X;
    cin >> N >> V >> X;
    vector<pair<double,double> > v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].first >> v[i].second;
    }
    try {
      printf("Case #%d: %.8f\n", Ti, solve(N, V, X, v));
    } catch (impossible&) {
      printf("Case #%d: IMPOSSIBLE\n", Ti);
    }
  }
  return 0;
}
