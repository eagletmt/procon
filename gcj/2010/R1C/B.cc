#include <iostream>
#include <vector>
#include <limits>
#include <cmath>
using namespace std;

int solve(int L, int P, int C)
{
  if (L*C >= P) {
    return 0;
  } else {
    int m = numeric_limits<int>::max();
    for (int i = L+1; i < P; i++) {
      int a = max(solve(i, P, C), solve(L, i, C));
      m = min(m, a);
    }
    return m;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int L, P, C;
    cin >> L >> P >> C;

    int cnt = 0;
    while (L*C < P) {
      cnt++;
      L *= C;
    }
    int ans;
    if (cnt != 0) {
      ans = log2((double)cnt);
      ans++;
    } else {
      ans = 0;
    }

    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}

