#include <iostream>
#include <vector>
using namespace std;
static const int N = 1<<15;

int main()
{
  vector<bool> sieve(N, false);
  vector<int> primes;
  for (int i = 2; i < N; i++) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i+i; j < N; j += i) {
        sieve[j] = true;
      }
    }
  }

  int n;
  while (cin >> n && n != 0) {
    int ans = 0;
    for (int i = 0; primes[i] <= n/2; i++) {
      if (!sieve[n-primes[i]]) {
        ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
