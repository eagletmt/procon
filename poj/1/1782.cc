#include <iostream>
#include <vector>
using namespace std;

string rle(const string& line)
{
  string ans;
  char last = 'X';
  int len = 1;
  for (string::const_iterator it(line.begin()); it != line.end(); ++it) {
    if (last == *it) {
      if (len == 9) {
        ans += string("9") + last;
        len = 1;
      } else {
        ++len;
      }
    } else {
      ans += string(1, '0'+len) + last;
      len = 1;
    }
    last = *it;
  }
  ans += string(1, '0'+len) + last;
  ans = ans.substr(2);
  return ans;
}

string comp(const string& s)
{
  string ans = "";
  string singles = "";
  for (string::size_type i = 0; i < s.size()/2; i++) {
    const int len = s[2*i]-'0';
    const char c = s[2*i+1];
    if (len == 1) {
      if (singles.empty()) {
        ans += string("1");
      }
      singles += c;
      if (c == '1') {
        singles += "1";
      }
    } else {
      if (!singles.empty()) {
        ans += singles + "1";
      }
      singles = "";
      ans += string(1, s[2*i]) + c;
    }
  }
  if (!singles.empty()) {
    ans += singles + "1";
  }
  return ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    cout << comp(rle(line)) << endl;
  }
  return 0;
}