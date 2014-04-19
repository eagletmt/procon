#include <iostream>
using namespace std;

int solve(int n, int k)
{
  int ans = 0;
  int cig = n;
  int butts = 0;
  while (cig > 0) {
    ans += cig;
    butts += cig;
    cig = butts / k;
    butts %= k;
  }
  return ans;
}

int main()
{
  int n, k;
  while (cin >> n >> k) {
    cout << solve(n, k) << endl;
  }
  return 0;
}
