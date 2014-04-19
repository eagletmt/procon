#include <iostream>
#include <sstream>
using namespace std;

string solve(string n)
{
  while (n.size() > 1) {
    int s = 0;
    for (string::const_iterator it(n.begin()); it != n.end(); ++it) {
      s += *it - '0';
    }
    ostringstream ss;
    ss << s;
    n = ss.str();
  }
  return n;
}

int main(void)
{
  string n;
  while (cin >> n && n != "0") {
    cout << solve(n) << endl;
  }
  return 0;
}
