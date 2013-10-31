#include <iostream>
#include <algorithm>
using namespace std;

int main()
{
  static int ans[101][10];
  for (int n = 2; n <= 100; n++) {
    copy(ans[n-1], ans[n-1] + 10, ans[n]);
    int seen[101];
    fill_n(seen, 101, 0);
    int x = 1;
    while (x != 0 && !seen[x]) {
      seen[x] = 1;
      x *= 10;
      ++ans[n][x/n];
      x %= n;
    }
  }

  for (int n, k; cin >> n >> k;) {
    cout << ans[n][k] << endl;
  }
  return 0;
}
