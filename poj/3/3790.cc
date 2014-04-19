#include <iostream>
#include <vector>
using namespace std;

int main()
{
  static int dp[1001];
  for (int i = 1; i <= 1000; i++) {
    dp[i] = 1;
    for (int j = 1; j < i; j++) {
      if ((i-j) % 2 == 0) {
        dp[i] += dp[(i-j)/2];
      }
    }
    if (i % 2 == 0) {
      dp[i] += dp[i/2];
    }
  }
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int x;
    cin >> x;
    cout << Ti << " " << dp[x] << endl;
  }
  return 0;
}
