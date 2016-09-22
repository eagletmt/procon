#include <iostream>
#include <vector>
using namespace std;

int main() {
  int N;
  cin >> N;
  string s;
  cin >> s;

  vector<int> xs(N);
  for (int i = 0; i < N; i++) {
    cin >> xs[i];
  }

  static const int INF = 1000000000;
  int ans = INF;
  for (int i = 0; i < N - 1; i++) {
    if (s[i] == 'R' && s[i + 1] == 'L') {
      ans = min(ans, (xs[i + 1] - xs[i]) / 2);
    }
  }
  if (ans == INF) {
    ans = -1;
  }
  cout << ans << endl;

  return 0;
}
