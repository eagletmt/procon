#include <iostream>
#include <vector>
#include <deque>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int R, k, N;
    cin >> R >> k >> N;
    deque<int> v;
    for (int i = 0; i < N; i++) {
      int g;
      cin >> g;
      v.push_back(g);
    }

    int pos = 0;
    vector<bool> seen(N, false);
    int ans = 0;
    for (int i = 0; i < R; i++) {
      if (seen[pos]) {
        ans *= R/(pos+1);
        i = R - R%i;
        fill(seen.begin(), seen.end(), false);
      } else {
        int a = 0;
        //seen[pos] = true;
        for (int j = 0; j < N; j++, pos++) {
          if (a + v.front() <= k) {
            a += v.front();
            v.push_back(v.front());
            v.pop_front();
          } else {
            break;
          }
        }
        pos %= N;
        ans += a;
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }

  return 0;
}

