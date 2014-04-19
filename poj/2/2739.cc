#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  static const int N = 10000;

  vector<bool> sieve(N+1, false);
  vector<int> primes;
  for (int i = 2; i <= N; i++) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i*2; j <= N; j += i) {
        sieve[j] = true;
      }
    }
  }

  vector<int> sums(N+1, 0);
  for (vector<int>::const_iterator it(primes.begin()); it != primes.end(); ++it) {
    int s = 0;
    for (vector<int>::const_iterator jt(it); jt != primes.end() && s+*jt <= N; ++jt) {
      s += *jt;
      sums[s]++;
    }
  }

  int n;
  while (cin >> n && n != 0) {
    cout << sums[n] << endl;
  }

  return 0;
}
