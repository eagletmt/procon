#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

double cross(const P& a, const P& b)
{
  return imag(conj(a) * b);
}

double area2(const vector<P>& v)
{
  double a = 0.0;
  const int N = v.size();
  for (int i = 0; i < N; i++) {
    a += cross(v[i], v[(i+1)%N]);
  }
  return abs(a)/2.0;
}

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<P> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].real() >> v[i].imag();
    }
    double m;
    cin >> m;
    printf("BAR LENGTH: %.2f\n", m/area2(v));
  }
  return 0;
}
