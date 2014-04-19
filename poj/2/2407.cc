#include <cstdio>
using namespace std;

long long euler(long long n)
{
  long long ans = 1LL;
  for (int i = 2; i*i <= n; i++) {
    if (n % i == 0) {
      long long p = 1;
      while (n % i == 0) {
        n /= i;
        p *= i;
      }
      ans *= p - p/i;
    }
  }
  if (n != 1LL) {
    ans *= n - 1LL;
  }
  return ans;
}

int main()
{
  long long n;
  while (scanf("%lld", &n) != EOF && n != 0LL) {
    printf("%lld\n", euler(n));
  }
  return 0;
}