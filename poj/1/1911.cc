#include <iostream>
#include <vector>
#include <set>
#include <cctype>
using namespace std;
#define FAIL throw ill_formed()

struct ill_formed {};

string tagname(const string& s)
{
  if (s[0] == '/') {
    for (string::const_iterator it = s.begin()+1; it != s.end(); ++it) {
      if (!isalnum(*it) && *it != '-') {
        FAIL;
      }
    }
    return s;
  } else {
    string name;
    for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
      if (*it == ' ') {
        return name;
      } else {
        if (!isalnum(*it) && *it != '-') {
          FAIL;
        }
        name += *it;
      }
    }
    return s;
  }
}

vector<string> tags(const string& s)
{
  vector<string> ret;
  string t;
  bool in_tag = false, in_dquote = false;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    if (in_dquote) {
      if (*it == '"') {
        in_dquote = false;
        t += *it;
      }
    } else {
      if (*it == '<') {
        if (in_tag) {
          FAIL;
        }
        in_tag = true;
        if (!t.empty()) {
          FAIL;
        }
      } else if (*it == '>') {
        if (!in_tag) {
          FAIL;
        }
        in_tag = false;
        if (t.empty()) {
          FAIL;
        }
        if (t[t.size()-1] == '/') {
          const string u = t.substr(0, t.size()-2);
          const string v = tagname(u);
          ret.push_back(v);
          ret.push_back("/" + v);
        } else {
          ret.push_back(tagname(t));
        }
        t.clear();
      } else if (*it == '"') {
        in_dquote = true;
        t += *it;
      } else {
        if (in_tag) {
          t += *it;
        }
      }
    }
  }
  return ret;
}

typedef vector<string>::const_iterator Iterator;

void ok(Iterator& it, const Iterator& last, set<string> used)
{
  const string name = *it;
  if (used.count(name)) {
    FAIL;
  }
  used.insert(name);
  ++it;
  if (it == last) {
    FAIL;
  }
  while ((*it)[0] != '/') {
    ok(it, last, used);
    if (it == last) {
      FAIL;
    }
  }
  if (*it != "/" + name) {
    FAIL;
  }
  ++it;
}

void check(string& s)
{
  const vector<string> v = tags(s);
  Iterator it = v.begin(), last = v.end();
  set<string> used;
  ok(it, last, used);
  if (it != last) {
    FAIL;
  }
}

void solve(string& s) try
{
  check(s);
  cout << "well-formed" << endl;
} catch (const ill_formed&) {
  cout << "non well-formed" << endl;
}

int main()
{
  static const string BEGIN = "<?xml version=\"1.0\"?>", END = "<?end?>";
  string s, t;
  while (getline(cin, s) && s != END) {
    if (s == BEGIN) {
      if (!t.empty()) {
        solve(t);
      }
      t.clear();
    } else {
      t += " " + s;
    }
  }
  if (!t.empty()) {
    solve(t);
  }
  return 0;
}