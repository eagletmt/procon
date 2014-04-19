#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int A, Y;
    cin >> A >> Y;
    int D;
    cin >> D;
    vector<pair<int,int> > b(D);
    for (int i = 0; i < D; i++) {
      cin >> b[i].first >> b[i].second;
      b[i].first /= 1000;
    }

    static const int M = 1000000;
    static int dp[M];
    fill_n(dp, M, 0);
    for (int i = 0; i < D; i++) {
      for (int j = 0; j < M; j++) {
        if (j + b[i].first < M) {
          dp[j + b[i].first] = max(dp[j + b[i].first], dp[j] + b[i].second);
        }
      }
    }
    int ans = A;
    for (int i = 0; i < Y; i++) {
      ans += dp[ans/1000];
    }
    cout << ans << endl;
  }
  return 0;
}