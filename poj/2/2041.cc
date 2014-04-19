#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

string invJ(string s)
{
  const char c = *s.rbegin();
  copy(s.rbegin()+1, s.rend(), s.rbegin());
  *s.begin() = c;
  return s;
}

string invC(string s)
{
  const char c = *s.begin();
  copy(s.begin()+1, s.end(), s.begin());
  *s.rbegin() = c;
  return s;
}

string invE(string s)
{
  const string::size_type l = s.size();
  swap_ranges(s.begin(), s.begin() + l/2, s.begin() + (l+1)/2);
  return s;
}

string invA(string s)
{
  reverse(s.begin(), s.end());
  return s;
}

string invM(string s)
{
  for (string::iterator it(s.begin()); it != s.end(); ++it) {
    if (isdigit(*it)) {
      *it = (*it-'0'+1)%10 + '0';
    }
  }
  return s;
}

string invP(string s)
{
  for (string::iterator it(s.begin()); it != s.end(); ++it) {
    if (isdigit(*it)) {
      *it = (*it-'0'+9)%10 + '0';
    }
  }
  return s;
}

int main(void)
{
  int n;
  cin >> n;
  while (n-- > 0) {
    string order, message;
    cin >> order >> message;
    for (string::const_reverse_iterator it(order.rbegin()); it != order.rend(); ++it) {
      switch (*it) {
        case 'J':
          message = invJ(message);
          break;
        case 'C':
          message = invC(message);
          break;
        case 'E':
          message = invE(message);
          break;
        case 'A':
          message = invA(message);
          break;
        case 'P':
          message = invP(message);
          break;
        case 'M':
          message = invM(message);
          break;
      }
    }
    cout << message << endl;
  }
  return 0;
}
