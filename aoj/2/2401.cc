#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

int formula(int s, Iterator& it, const Iterator& last)
{
  switch (*it) {
    case 'T':
      ++it;
      return 1;
    case 'F':
      ++it;
      return 0;
    case '-':
      ++it;
      return !formula(s, it, last);
    case '(':
      {
        ++it;
        const int l = formula(s, it, last);
        const char op = *it;
        ++it;
        if (op == '-') {
          if (*it != '>') {
            throw ">";
          }
          ++it;
        }
        const int r = formula(s, it, last);
        if (*it != ')') {
          throw ")";
        }
        ++it;
        switch (op) {
          case '*':
            return l && r;
          case '+':
            return l || r;
          case '-':
            return !l || r;
          default:
            throw "op";
        }
      }
    default:
      if ('a' <= *it && *it <= 'k') {
        const char c = *it;
        ++it;
        return !!(s & (1<<(c-'a')));
      } else {
        throw "l";
      }
  }
  throw "eof";
}

bool solve(const string& lhs, const string& rhs)
{
  for (int s = 0; s < (1<<11); s++) {
    Iterator it = lhs.begin(), ilast = lhs.end();
    Iterator jt = rhs.begin(), jlast = rhs.end();
    int l = formula(s, it, ilast);
    int r = formula(s, jt, jlast);
    if (it != ilast) {
      throw "ilast";
    }
    if (jt != jlast) {
      throw "jlast";
    }
    if (l != r) {
      return false;
    }
  }
  return true;
}

int main()
{
  string s;
  while (getline(cin, s) && s != "#") {
    replace(s.begin(), s.end(), '=', ' ');
    istringstream iss(s);
    string lhs, rhs;
    iss >> lhs >> rhs;
    cout << (solve(lhs, rhs) ? "YES" : "NO") << endl;
  }
  return 0;
}
