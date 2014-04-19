#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

#define N 1000000

int main(void)
{
  bool sieve[N] = {true, false};
  vector<int> primes;

  for (int i = 2; i <= N; i++) {
    if (!sieve[i-1]) {
      primes.push_back(i);
      for (int j = i+i; j <= N; j += i) {
        sieve[j-1] = true;
      }
    }
  }

  for (;;) {
    int n;
    cin >> n;
    if (n == 0) {
      break;
    }

    for (vector<int>::iterator it = primes.begin(); it != primes.end(); ++it) {
      if (!sieve[(n-*it)-1]) {
        cout << n << " = " << *it << " + " << n - *it << endl;
        break;
      }
    }
  }
  
  return 0;
}
