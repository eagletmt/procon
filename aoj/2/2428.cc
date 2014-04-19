#include <iostream>
#include <cctype>
using namespace std;

typedef string::const_iterator Iterator;

struct parse_error {};

void check_range(int n)
{
  if (n < 0 || 1024 <= n) {
    throw parse_error();
  }
}

int expr(Iterator& it, const Iterator& last);
int term(Iterator& it, const Iterator& last);

int number(Iterator& it, const Iterator& last)
{
  if (it == last) {
    throw parse_error();
  }
  int n = 0;
  while (it != last && isdigit(*it)) {
    n = 2*n + (*it - '0');
    ++it;
    check_range(n);
  }
  return n;
}

int factor(Iterator& it, const Iterator& last)
{
  if (it == last) {
    throw parse_error();
  }
  if (*it == '(') {
    ++it;

    int n = factor(it, last);
    if (it == last) {
      throw parse_error();
    }
    if (*it == '*') {
      while (it != last && *it == '*') {
        ++it;
        n *= factor(it, last);
        check_range(n);
      }
      while (it != last && (*it == '+' || *it == '-')) {
        const char op = *it;
        ++it;
        int m = term(it, last);
        if (op == '+') {
          n += m;
        } else {
          n -= m;
        }
        check_range(n);
      }
    } else if (*it == '+' || *it == '-') {
      while (it != last && (*it == '+' || *it == '-')) {
        const char op = *it;
        ++it;
        int m = term(it, last);
        if (op == '+') {
          n += m;
        } else {
          n -= m;
        }
        check_range(n);
      }
    } else {
      throw parse_error();
    }

    if (it == last || *it != ')') {
      throw parse_error();
    }
    ++it;
    return n;
  } else if (isdigit(*it)) {
    return number(it, last);
  } else {
    throw parse_error();
  }
}

int term(Iterator& it, const Iterator& last)
{
  int n = factor(it, last);
  while (it != last && *it == '*') {
    ++it;
    n *= factor(it, last);
    check_range(n);
  }
  return n;
}

int expr(Iterator& it, const Iterator& last)
{
  int n = term(it, last);
  while (it != last && (*it == '+' || *it == '-')) {
    const char op = *it;
    ++it;
    int m = term(it, last);
    if (op == '+') {
      n += m;
    } else {
      n -= m;
    }
    check_range(n);
  }
  return n;
}

int main()
{
  string s;
  getline(cin, s);
  int a[5];
  static const char tbl[] = "01+-*()";
  int ans = -1;
  for (a[0] = 0; a[0] < 7; a[0]++) {
    for (a[1] = 0; a[1] < 7; a[1]++) {
      for (a[2] = 0; a[2] < 7; a[2]++) {
        for (a[3] = 0; a[3] < 7; a[3]++) {
          for (a[4] = 0; a[4] < 7; a[4]++) {
            string t = s;
            for (int i = 0; i < 5; i++) {
              string::size_type n = t.find('.');
              if (n != string::npos) {
                t[n] = tbl[a[i]];
              }
            }
            try {
              Iterator it = t.begin(), last = t.end();
              int n = expr(it, last);
              if (it == last) {
                ans = max(ans, n);
              }
            } catch (const parse_error&) {
            }
          }
        }
      }
    }
  }
  cout << ans << endl;
  return 0;
}
