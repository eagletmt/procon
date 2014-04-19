#include <iostream>
#include <cstdio>
using namespace std;

int popcount(long long x)
{
  int c = 0;
  for (int i = 0; i < 64; i++) {
    if (x & (1LL<<i)) {
      ++c;
    }
  }
  return c;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    long long N;
    cin >> N;
    int ans = 0;
    for (long long a = 1LL; a <= N; a <<= 1) {
      ans = max(ans, popcount(a-1) + popcount(N-a+1));
    }
    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
