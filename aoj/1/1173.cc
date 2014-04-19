#include <iostream>
#include <stack>
using namespace std;

bool check(const string& s)
{
  stack<char> stk;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    switch (*it) {
      case '(':
        stk.push(')');
        break;
      case '[':
        stk.push(']');
        break;
      case ')':
      case ']':
        if (stk.empty() || stk.top() != *it) {
          return false;
        }
        stk.pop();
        break;
    }
  }
  return stk.empty();
}

int main()
{
  for (string s; getline(cin, s) && s != ".";) {
    cout << (check(s) ? "yes" : "no") << endl;
  }
  return 0;
}
