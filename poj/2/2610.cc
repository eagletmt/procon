#include <iostream>
#include <cstdio>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

int main()
{
  P gopher, dog;
  cin >> gopher.real() >> gopher.imag() >> dog.real() >> dog.imag();
  P hole;
  while (cin >> hole.real() >> hole.imag()) {
    if (2*abs(hole-gopher) < abs(hole-dog)) {
      printf("The gopher can escape through the hole at (%.3f,%.3f).\n", hole.real(), hole.imag());
      return 0;
    }
  }
  puts("The gopher cannot escape.");
  return 0;
}
