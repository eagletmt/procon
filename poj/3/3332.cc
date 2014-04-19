#include <iostream>
#include <string>
#include <sstream>
using namespace std;

struct skip_white {
  template <class Iterator>
  bool operator()(Iterator& it, const Iterator& last) const
  {
    while (*it == ' ' && it != last) {
      ++it;
    }
    return true;
  }
};

struct digit {
  template <class Iterator>
  bool operator()(Iterator& it, const Iterator& last) const
  {
    if (it != last && '0' <= *it && *it <= '9') {
      ++it;
      return true;
    } else {
      return false;
    }
  }
};

template <class Parser>
struct many1 {
  Parser p;
  many1(const Parser& p_) : p(p_) {}
  template <class Iterator>
  bool operator()(Iterator& it, const Iterator& last) const
  {
    if (!p(it, last)) {
      return false;
    } else {
      while (p(it, last));
      return true;
    }
  }
};

template <class Iterator>
struct literal_char {
  typedef typename iterator_traits<Iterator>::value_type value_type;
  value_type c;
  literal_char(const value_type& c_)
    : c(c_)
  {}
  bool operator()(Iterator& it, const Iterator& last) const
  {
    if (it != last && *it == c) {
      ++it;
      return true;
    } else {
      return false;
    }
  }
};

template <class Iterator>
bool digits(Iterator& it, const Iterator& last)
{
  const literal_char<string::const_iterator> plus('+'), minus('-');

  const Iterator save = it;
  plus(it, last) || minus(it, last);
  if (many1<digit>(digit())(it, last)) {
    return true;
  } else {
    it = save;
    return false;
  }
}

int main()
{
  const literal_char<string::const_iterator> dot('.'), e('e'), E('E');

  string t;
  getline(cin, t);
  istringstream tt(t);
  int T;
  tt >> T;
  while (T-- > 0) {
    string s;
    getline(cin, s);
    string::const_iterator it = s.begin(), end = s.end();
    skip_white()(it, end);

    if (digits(it, end)) {
      if (dot(it, end)) {
        if (digits(it, end)) {
          if (e(it, end) || E(it, end)) {
            if (digits(it, end)
                && skip_white()(it, end)
                && it == end) {
              cout << "LEGAL" << endl;
            } else {
              cout << "ILLEGAL" << endl;
            }
          } else {
            skip_white()(it, end);
            if (it == end) {
              cout << "LEGAL" << endl;
            } else {
              cout << "ILLEGAL" << endl;
            }
          }
        } else {
          cout << "ILLEGAL" << endl;
        }
      } else {
        if (e(it, end) || E(it, end)) {
          if (digits(it, end)
              && skip_white()(it, end)
              && it == end) {
            cout << "LEGAL" << endl;
          } else {
            cout << "ILLEGAL" << endl;
          }
        } else {
          skip_white()(it, end);
          if (it == end) {
            cout << "LEGAL" << endl;
          } else {
            cout << "ILLEGAL" << endl;
          }
        }
      }
    } else {
      cout << "ILLEGAL" << endl;
    }
  }
  return 0;
}