#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    vector<int> candy(N);
    int s = 0;
    for (int i = 0; i < N; i++) {
      cin >> candy[i];
      s ^= candy[i];
    }
    if (s != 0) {
      cout << "Case #" << Ti << ": NO" << endl;
      continue;
    }

    int ans = 0;
    for (s = 0; s < (1<<N); s++) {
      int x = 0, y = 0;
      int a = 0, b = 0;
      for (int i = 0; i < N; i++) {
        if (s & (1<<i)) {
          x ^= candy[i];
          a += candy[i];
        } else {
          y ^= candy[i];
          b += candy[i];
        }
      }
      if (x == y && a != 0 && b != 0) {
        ans = max(ans, a);
      }
    }
    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
