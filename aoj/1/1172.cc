#include <iostream>
using namespace std;

int main()
{
  static const int MAXN = 123456*2;
  static bool sieve[MAXN+1];
  for (int i = 2; i <= MAXN; i++) {
    if (!sieve[i]) {
      for (int j = i+i; j <= MAXN; j += i) {
        sieve[j] = true;
      }
    }
  }

  int N;
  while (cin >> N && N != 0) {
    int ans = 0;
    for (int i = N+1; i <= 2*N; i++) {
      if (!sieve[i]) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
