#include <iostream>
#include <queue>
using namespace std;

int main()
{
  string red, green, down;
  while (cin >> red && red != "-") {
    cin >> green >> down;
    queue<char> top, left;
    for (string::const_iterator it(red.begin()); it != red.end(); ++it) {
      top.push(*it);
    }
    for (string::const_iterator it(green.begin()); it != green.end(); ++it) {
      left.push(*it);
    }

    char center = left.front();
    left.pop();
    string ans;
    for (string::const_iterator it(down.begin()); it != down.end();) {
      if (center == *it) {
        // push_down
        center = top.front();
        top.pop();
        ++it;
      } else {
        // push_right
        ans += center;
        center = left.front();
        left.pop();
      }
    }
    while (!left.empty()) {
      ans += center;
      center = left.front();
      left.pop();
    }
    ans += center;
    cout << ans << endl;
  }
  return 0;
}
