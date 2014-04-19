#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

int main(void)
{
  string s;

  while (getline(cin, s) && s != "#") {
    const string reserved = " !$%()*";
    cout.setf(ios::hex, ios::basefield);
    for (string::const_iterator it(s.begin()); it != s.end(); ++it) {
      if (reserved.find(*it) == string::npos) {
        cout << *it;
      } else {
        cout << '%' << (int)*it;
      }
    }
    cout << endl;
  }
  return 0;
}