#include <iostream>
#include <cstdio>
#include <vector>
using namespace std;

long long gcd(long long a, long long b)
{
  if (a < b) {
    swap(a, b);
  }
  long long r = a % b;
  while (r != 0) {
    a = b;
    b = r;
    r = a % b;
  }
  return b;
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<int> p(M);
    for (int i = 0; i < M; i++) {
      cin >> p[i];
    }

    long long n = 0LL;
    double sum = 0.0;
    for (int s = 0; s < (1<<M); s++) {
      const int sign = __builtin_popcount(s) & 1 ? 1 : -1;
      long long lcm = 1LL;
      long long m;
      for (int i = 0; i < M; i++) {
        if (s & (1<<i)) {
          long long g = gcd(lcm, p[i]);
          if (lcm*p[i] > N*g) {
            goto NEXT;
          }
          lcm *= static_cast<long long>(p[i]/g);
        }
      }
      m = N/lcm;
      n += sign * m;
      sum += sign * lcm * m*(m+1LL)/2LL;
NEXT:
      ;
    }
    printf("%.6f\n", n == 0LL ? 0.0 : sum/n);
  }
  return 0;
}
