#include <iostream>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int mm, ss;
    char c;
    cin >> mm >> c >> ss;
    int ans;
    if (ss == 0) {
      if (mm <= 12) {
        ans = mm+12;
      } else {
        ans = mm-12;
      }
    } else {
      ans =0;
    }
    cout << ans << endl;
  }
  return 0;
}