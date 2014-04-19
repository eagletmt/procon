#include <iostream>
#include <vector>
using namespace std;

int main()
{
  vector<int> v(5);
  while (cin >> v[0] && v[0] != 0) {
    vector<bool> t(3, false);
    --v[0];
    t[v[0]] = true;
    vector<int> ans(5, 3);
    for (int i = 1; i < 5; i++) {
      cin >> v[i];
      --v[i];
      t[v[i]] = true;
    }

    for (int a = 0; a < 3; a++) {
      if (!t[a]) {
        if (!t[(a+1)%3] || !t[(a+2)%3]) {
          // all a+1 or a+2
        } else {
          // a+1 wins, a+2 lose
          for (int i = 0; i < 5; i++) {
            if (v[i] == (a+1)%3) {
              ans[i] = 1;
            } else if (v[i] == (a+2)%3) {
              ans[i] = 2;
            } else {
              while (1) {}
            }
          }
          break;
        }
      }
    }
    for (int i = 0; i < 5; i++) {
      cout << ans[i] << endl;
    }
  }
  return 0;
}
