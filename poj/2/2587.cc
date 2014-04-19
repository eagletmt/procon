#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

struct triple
{
  double x, y, z;
  double abs() const { return x*x + y*y + z*z; }
  double operator*(const triple& that) const { return x*that.x + y*that.y + z*that.z; }
};

double dist(const triple& a, const triple& b)
{
  return acos((a*b) / (a.abs()*b.abs()));
}

int main()
{
  const double PI = atan2(+0.0, -0.0);
  int N;
  scanf("%d", &N);
  vector<pair<double,double> > w(N);
  vector<triple> v(N);
  for (int i = 0; i < N; i++) {
    scanf("%lf %lf", &w[i].first, &w[i].second);
    const double theta = w[i].first/180.0*PI;
    const double phi = w[i].second/180.0*PI;
    v[i].x = cos(theta)*cos(phi);
    v[i].y = cos(theta)*sin(phi);
    v[i].z = sin(theta);
  }

  int ans = -1;
  double a = 1e10;
  for (int i = 0; i < N; i++) {
    double m = 0.0;
    for (int j = 0; j < N; j++) {
      if (i != j) {
        m = max(m, dist(v[i], v[j]));
      }
    }
    if (m < a) {
      a = m;
      ans = i;
    }
  }
  printf("%.2f %.2f\n", w[ans].first, w[ans].second);
  return 0;
}