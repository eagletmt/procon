#include <iostream>
#include <vector>
using namespace std;

struct expr
{
  typedef enum { NODE, LEAF } expr_type;
  expr_type type;
  int len;
  vector<expr> cs;
  string genom;
};

typedef string::const_iterator Iterator;
pair<expr,Iterator> parse_one(Iterator it, const Iterator& last)
{
  if (it == last) {
    throw "eof";
  }
  if ('A' <= *it &&  *it <= 'Z') {
    string genom;
    while (it != last && 'A' <= *it &&  *it <= 'Z') {
      genom += *it;
      ++it;
    }
    expr e;
    e.type = expr::LEAF;
    e.len = 1;
    e.genom = genom;
    return make_pair(e, it);
  } else {
    int len = 0;
    while (it != last && '0' <= *it && *it <= '9') {
      len = 10*len + (*it - '0');
      ++it;
    }
    if (*it == '(') {
      ++it;
      expr e;
      e.type = expr::NODE;
      e.len = len;
      while (*it != ')') {
        pair<expr,Iterator> p = parse_one(it, last);
        e.cs.push_back(p.first);
        it = p.second;
      }
      ++it;
      return make_pair(e, it);
    } else {
      expr e;
      e.type = expr::LEAF;
      e.len = len;
      e.genom = *it;
      ++it;
      return make_pair(e, it);
    }
  }
}

expr parse(Iterator it, const Iterator& last)
{
  expr e;
  e.type = expr::NODE;
  e.len = 1;
  while (it != last) {
    const pair<expr,Iterator> p = parse_one(it, last);
    e.cs.push_back(p.first);
    it = p.second;
  }
  return e;
}

string expand(const expr& e, unsigned idx)
{
  if (e.type == expr::NODE) {
    string t = "";
    for (vector<expr>::const_iterator it(e.cs.begin()); it != e.cs.end(); ++it) {
      t += expand(*it, idx);
      if (t.size() > idx) {
        return t.substr(0, idx+1);
      }
    }
    string g = "";
    for (int i = 0; i < e.len; i++) {
      g += t;
      if (g.size() > idx) {
        return g.substr(0, idx+1);
      }
    }
    return g.substr(0, idx+1);
  } else {
    string g = "";
    for (int i = 0; i < e.len; i++) {
      g += e.genom;
    }
    return g.substr(0, idx+1);
  }
}

int main()
{
  string s;
  unsigned idx;
  while (cin >> s >> idx && s != "0") {
    const expr e = parse(s.begin(), s.end());
    const string t = expand(e, idx);
    if (idx < t.size()) {
      cout << t[idx] << endl;
    } else {
      cout << "0" << endl;
    }
  }
  return 0;
}
