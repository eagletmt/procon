#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

double area(vector<P> polygon)
{
  const int N = polygon.size();
  double s = 0.0;
  for (int i = 0; i < N; i++) {
    s += polygon[i].real()*polygon[(i+1)%N].imag() - polygon[i].imag()*polygon[(i+1)%N].real();
  }
  return abs(s)/2.0;
}

int main()
{
  int c = 1;
  int n;
  while (cin >> n && n != 0) {
    vector<P> polygon(n);
    for (int i = 0; i < n; i++) {
      cin >> polygon[i].real() >> polygon[i].imag();
    }
    
    printf("%d %.1f\n", c, area(polygon));
    c++;
  }
  return 0;
}
