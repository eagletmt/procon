#include <iostream>
using namespace std;

unsigned long long pow(unsigned long long a, unsigned long long p, unsigned long long m)
{
  if (p == 0) {
    return 1;
  } else if (p % 2 == 1) {
    return (a * pow(a, p-1ULL, m)) % m;
  } else {
    const unsigned long long t = pow(a, p/2ULL, m) % m;
    return (t*t) % m;
  }
}

static const int M = 100000;
static bool sieve[M+1];
static unsigned primes[M+1];
static int len;

bool prime(unsigned long long n)
{
  for (int i = 0; i < len && primes[i]*primes[i] <= n; i++) {
    if (n % static_cast<unsigned long long>(primes[i]) == 0) {
      return false;
    }
  }
  return true;
}

int main()
{
  sieve[1] = true;
  for (int i = 2; i <= M; i++) {
    if (!sieve[i]) {
      primes[len++] = i;
      for (int j = 2*i; j <= M; j += i) {
        sieve[j] = true;
      }
    }
  }

  unsigned long long a, p;
  while (cin >> p >> a && a != 0) {
    if (prime(p) || pow(a, p, p) != a) {
      cout << "no" << endl;
    } else {
      cout << "yes" << endl;
    }
  }
  return 0;
}