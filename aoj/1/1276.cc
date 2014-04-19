#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  static const int M = 1299709;
  vector<int> primes;
  vector<bool> sieve(M+1, false);
  sieve[1] = true;
  for (int i = 2; i <= M; i++) {
    if (!sieve[i]) {
      primes.push_back(i);
      for (int j = i+i; j <= M; j += i) {
        sieve[j] = true;
      }
    }
  }

  int k;
  while (cin >> k && k != 0) {
    vector<int>::const_iterator it = lower_bound(primes.begin(), primes.end(), k);
    if (*it == k) {
      cout << 0 << endl;
    } else {
      cout << (*it - *(it-1)) << endl;
    }
  }
  return 0;
}
