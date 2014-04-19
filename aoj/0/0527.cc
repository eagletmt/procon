#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    int x;
    cin >> x;
    vector<int> v(1, 1);
    int ans = x == 0 ? 1 : 0;
    int prev = x;
    for (int i = 1; i < N; i++) {
      cin >> x;
      if (prev == x) {
        v.back()++;
        if (x == 0) {
          ans++;
        }
      } else {
        if (i % 2 == 0) {
          v.push_back(1);
          if (x == 0) {
            ans++;
          }
        } else {
          if (v.size() == 1) {
            v.back()++;
            if (x == 0) {
              ans = v.back();
            } else {
              ans = 0;
            }
          } else {
            const int y = v.back();
            v.pop_back();
            v.back() += y + 1;
            if (x == 0) {
              ans += y + 1;
            } else {
              ans -= y;
            }
          }
        }
      }
      prev = x;
    }
    cout << ans << endl;
  }
  return 0;
}
