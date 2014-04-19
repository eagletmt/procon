#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  while (cin >> n) {
    vector<int> s(n);
    for (int i = 0; i < n; i++) {
      cin >> s[i];
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int len = 0;
      int cur_max = s[i];
      for (int j = i+1; j < n && s[i] < s[j]; j++) {
        if (s[j] >= cur_max) {
          len = j-i;
          cur_max = s[j];
        }
      }
      ans = max(ans, len);
      i += len;
    }
    cout << (ans == 0 ? -1 : ans) << endl;
  }
  return 0;
}
