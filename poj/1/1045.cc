#include <iostream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(void)
{
  double Vs, R, C;
  int n;
  cin >> Vs >> R >> C >> n;

  while (n-- > 0) {
    double w;
    cin >> w;
    printf("%.3f\n",  Vs / sqrt(1.0/(C*R*w*w) + 1.0));
  }

  return 0;
}