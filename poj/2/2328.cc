#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int n;
  vector<bool> can(11, true);
  while (cin >> n && n != 0) {
    string s;
    cin >> s >> s;
    if (s == "high") {
      for (int i = n; i <= 10; i++) {
        can[i] = false;
      }
    } else if (s == "low") {
      for (int i = 1; i <= n; i++) {
        can[i] = false;
      }
    } else {
      // right on
      if (can[n]) {
        cout << "Stan may be honest" << endl;
      } else {
        cout << "Stan is dishonest" << endl;
      }
      can.assign(11, true);
    }
  }
  return 0;
}
