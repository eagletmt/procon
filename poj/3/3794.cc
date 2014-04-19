#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <cstring>
using namespace std;

int intcmp(int a, int b)
{
  if (a < b) {
    return -1;
  } else if (a > b) {
    return 1;
  } else {
    return 0;
  }
}

struct S
{
  string n;
  string s;
  bool int_p;
  S(const string& x, const string& t) : n(x), s(t), int_p(true) {}
  S(const string& t) : n(), s(t), int_p(false) {}
  int cmp(const S& o) const
  {
    if (int_p && o.int_p) {
      if (n.size() == o.n.size()) {
        return strcmp(n.c_str(), o.n.c_str());
      } else {
        return intcmp(n.size(), o.n.size());
      }
    } else {
      return strcmp(s.c_str(), o.s.c_str());
    }
  }
};

int cmp(const vector<S>& a, const vector<S>& b)
{
  const int N = a.size(), M = b.size(), K = min(N, M);
  for (int i = 0; i < K; i++) {
    const int r = a[i].cmp(b[i]);
    if (r != 0) {
      return r;
    }
  }
  return intcmp(N, M);
}

vector<S> lex(const string& s)
{
  vector<S> v;
  string buf;
  bool was_digit = false;
  bool neg = false;
  string::const_iterator it = s.begin();
  while (it != s.end()) {
    if (*it == '+') {
      if (was_digit) {
        buf += *it;
      } else {
        neg = false;
      }
      ++it;
      was_digit = false;
    } else if (*it == '-') {
      if (was_digit) {
        buf += *it;
      } else {
        neg = true;
      }
      ++it;
      was_digit = false;
    } else if (isdigit(*it)) {
      if (!buf.empty()) {
        v.push_back(S(buf));
        buf.clear();
      }
      string n;
      while (it != s.end() && isdigit(*it)) {
        if (n.empty() && *it == '0') {
          // leading zeros
        } else {
          n = *it + n;
        }
        buf += *it;
        ++it;
      }
      if (n.empty()) {
        n = "1";
      } else {
        if (neg) {
          n = "0" + n;
        } else {
          n = "2" + n;
        }
      }
      v.push_back(S(n, buf));
      buf.clear();
      was_digit = true;
    } else {
      buf += tolower(*it);
      was_digit = false;
      ++it;
    }
  }
  if (!buf.empty()) {
    v.push_back(buf);
  }
  return v;
}

int main()
{
  ios::sync_with_stdio(false);
  int N;
  cin >> N;
  for (int i = 0; i < N; i++) {
    string s, t;
    cin >> s >> t;
    cout << i+1 << " " << cmp(lex(s), lex(t)) << endl;
  }
  return 0;
}
