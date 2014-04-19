#include <iostream>
using namespace std;

int main()
{
  long long N;
  cin >> N;
  int ans = 0;
  for (long long e = 1; e < N; e *= 3LL) {
    ++ans;
  }
  cout << ans << endl;
  return 0;
}
