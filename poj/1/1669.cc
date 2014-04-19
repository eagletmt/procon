#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct gomi
{
  bool operator()(const char c) const
  {
    return c != '|' && c != '&' && c != '^' && c != '~' && c != '(' && c != ')' && !('a' <= c && c <= 'z');
  }
};

struct expr
{
  typedef enum { OR, AND, XOR, NOT, VAR } expr_type;
  expr_type type;
  char v;
  vector<expr> cs;
};

pair<expr, int> parse_or(const string& s, int i);

pair<expr,int> parse_factor(const string& s, int i)
{
  if (s[i] == '(') {
    const pair<expr,int> p = parse_or(s, i+1);
    return make_pair(p.first, p.second+1);
  } else if ('a' <= s[i] && s[i] <= 'z') {
    expr e;
    e.type = expr::VAR;
    e.v = s[i];
    return make_pair(e, i+1);
  } else {
    throw "parse error";
  }
}

pair<expr, int> parse_not(const string& s, int i)
{
  if (s[i] == '~') {
    expr e;
    e.type = expr::NOT;
    ++i;
    const pair<expr,int> q = parse_not(s, i);
    e.cs.push_back(q.first);
    return make_pair(e, q.second);
  } else {
    return parse_factor(s, i);
  }
}

pair<expr,int> parse_and(const string& s, int i)
{
  const pair<expr,int> p = parse_not(s, i);
  expr e = p.first;
  i = p.second;
  while (s[i] == '&') {
    expr f;
    f.type = expr::AND;
    ++i;
    const pair<expr,int> q = parse_not(s, i);
    f.cs.push_back(e);
    f.cs.push_back(q.first);
    i = q.second;
    e = f;
  }
  return make_pair(e, i);
}

pair<expr,int> parse_xor(const string& s, int i)
{
  const pair<expr,int> p = parse_and(s, i);
  expr e = p.first;
  i = p.second;
  while (s[i] == '^') {
    expr f;
    f.type = expr::XOR;
    ++i;
    const pair<expr,int> q = parse_and(s, i);
    f.cs.push_back(e);
    f.cs.push_back(q.first);
    i = q.second;
    e = f;
  }
  return make_pair(e, i);
}

pair<expr, int> parse_or(const string& s, int i)
{
  const pair<expr,int> p = parse_xor(s, i);
  expr e = p.first;
  i = p.second;
  while (s[i] == '|') {
    expr f;
    f.type = expr::OR;
    ++i;
    const pair<expr,int> q = parse_xor(s, i);
    f.cs.push_back(e);
    f.cs.push_back(q.first);
    i = q.second;
    e = f;
  }
  return make_pair(e, i);
}

string vars(const string& s)
{
  set<char> t;
  for (string::const_iterator it(s.begin()); it != s.end(); ++it) {
    if ('a' <= *it && *it <= 'z') {
      t.insert(*it);
    }
  }
  return string(t.begin(), t.end());
}

bool eval(const expr& e, const bool b[26])
{
  switch (e.type) {
    case expr::AND:
      return eval(e.cs[0], b) && eval(e.cs[1], b);
    case expr::OR:
      return eval(e.cs[0], b) || eval(e.cs[1], b);
    case expr::XOR:
      return eval(e.cs[0], b) ^ eval(e.cs[1], b);
    case expr::NOT:
      return !eval(e.cs[0], b);
    case expr::VAR:
      return b[e.v-'a'];
  }
  throw "not reached";
}

int main()
{
  int N;
  cin >> N;
  cin.ignore();
  for (int n = 1; n <= N; n++) {
    string line;
    getline(cin, line);
    line.erase(remove_if(line.begin(), line.end(), gomi()), line.end());
    const string vs = vars(line);
    const pair<expr, int> p = parse_or(line, 0);
    const pair<expr, int> q = parse_or(line, p.second);
    bool eqv = true;
    for (unsigned s = 0; s < (1<<vs.size()); ++s) {
      bool b[26];
      for (unsigned i = 0; i < vs.size(); ++i) {
        b[vs[i]-'a'] = (s & (1<<i)) != 0;
      }
      if (eval(p.first, b) != eval(q.first, b)) {
        eqv = false;
        break;
      }
    }
    cout << "Data set " << n << ": " << (eqv ? "Equivalent" : "Different") << endl;
  }
  return 0;
}