#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  static const int N = 100000;
  static const int M = 1299709;
  static int primes[N];
  static bool sieve[M+1];
  sieve[1] = true;
  int size = 0;
  for (int i = 2; i <= M; i++) {
    if (!sieve[i]) {
      primes[size++] = i;
      for (int j = i+i; j <= M; j += i) {
        sieve[j] = true;
      }
    }
  }

  int K;
  while (scanf("%d", &K) == 1 && K != 0) {
    const int *l = lower_bound(primes, primes+N, K);
    if (*l == K) {
      puts("0");
    } else {
      printf("%d\n", *l - *(l-1));
    }
  }
  return 0;
}