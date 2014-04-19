#include <iostream>
#include <iomanip>
#include <sstream>
using namespace std;

int main()
{
  int n;
  while (cin >> n && n != 0) {
    ostringstream oss;
    oss << oct << n;
    string s = oss.str();
    for (string::iterator it(s.begin()); it != s.end(); ++it) {
      static const char tbl[] = "01235789";
      *it = tbl[*it-'0'];
    }
    cout << s << endl;
  }
  return 0;
}
