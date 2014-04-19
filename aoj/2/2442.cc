#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;
static const double EPS = 1e-8;

bool check(const vector<P>& v, P& ans)
{
  int N = v.size();
  if (N % 2 != 0) {
    return false;
  }
  N /= 2;
  ans = (v[0] + v[N])*0.5;
  for (int i = 1; i < N; i++) {
    const P p = (v[i] + v[N+i])*0.5;
    if (abs(p - ans) > EPS) {
      return false;
    }
  }
  return true;
}

int main()
{
  int N;
  scanf("%d", &N);
  vector<P> v;
  for (int i = 0; i < N; i++) {
    double x, y;
    scanf("%lf %lf", &x, &y);
    v.push_back(P(x, y));
  }
  P ans;
  if (check(v, ans)) {
    printf("%.6f %.6f\n", ans.real(), ans.imag());
  } else {
    puts("NA");
  }
  return 0;
}
