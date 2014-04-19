#include <iostream>
#include <vector>
#include <sstream>
#include <cmath>
using namespace std;

pair<bool,int> read(string term)
{
  if (!term.empty() && term[term.size()-1] == 'x') {
    int x;
    istringstream iss(term);
    if (iss >> x) {
      return make_pair(true, x);
    } else {
      if (term[0] == '-') {
        return make_pair(true, -1);
      } else {
        return make_pair(true, 1);
      }
    }
  } else {
    int x;
    istringstream iss(term);
    if (iss >> x) {
      return make_pair(false, x);
    } else {
      if (!term.empty() && term[0] == '-') {
        return make_pair(true, -1);
      } else {
        return make_pair(true, 1);
      }
    }
  }
}

void solve(const string& s)
{
  string t = "";
  int v = 0, c = 0;
  bool eq_found = false;
  for (int i = 0; i < s.size(); i++) {
    if (s[i] == '=') {
      eq_found = true;
      const pair<bool,int> p = read(t);
      if (p.first) {
        v += p.second;
      } else {
        c += p.second;
      }
      t = "";
    } else if (s[i] == '+') {
      pair<bool,int> p = read(t);
      if (eq_found) {
        p.second = -p.second;
      }
      if (p.first) {
        v += p.second;
      } else {
        c += p.second;
      }
      t = "";
    } else if (s[i] == '-') {
      pair<bool,int> p = read(t);
      if (eq_found) {
        p.second = -p.second;
      }
      if (p.first) {
        v += p.second;
      } else {
        c += p.second;
      }
      t = "-";
    } else {
      t += s[i];
    }
  }
  pair<bool,int> p = read(t);
  if (p.first) {
    v -= p.second;
  } else {
    c -= p.second;
  }
  if (v == 0) {
    if (c == 0) {
      cout << "IDENTITY" << endl;
    } else {
      cout << "IMPOSSIBLE" << endl;
    }
  } else {
    const int r = floor(double(-c)/v);
    cout << r << endl;
  }
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    string s;
    cin >> s;
    solve(s);
  }
  return 0;
}
