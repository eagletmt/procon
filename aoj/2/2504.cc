#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <cctype>
using namespace std;

struct renamer
{
  map<string,int> m;
  int operator()(const string& s)
  {
    map<string,int>::const_iterator it = m.find(s);
    if (it == m.end()) {
      const int id = m.size();
      m.insert(make_pair(s, id));
      return id;
    } else {
      return it->second;
    }
  }
};

struct expr
{
  int op;
  int lit;
  int lhs, rhs;

  expr() : op(-1), lit(-1), lhs(-1), rhs(-1) {}

  expr operator~() const
  {
    expr e;
    if (lit_p()) {
      e.lit = lit^1;
    } else {
      e.op = op^1;
      e.lhs = lhs^1;
      e.rhs = rhs^1;
    }
    return e;
  }

  void dump() const
  {
    if (lit_p()) {
      cerr << lit << endl;
    } else {
      cerr << lhs << ' ' << (and_p() ? "&" : "|") << ' ' << rhs << endl;
    }
  }

  bool lit_p() const { return op == -1; }
  bool and_p() const { return op == 0; }
  bool or_p() const { return op == 1; }
};

typedef string::const_iterator Iterator;

expr parse_expr(Iterator& it, const Iterator& last, renamer& r);
expr parse_factor(Iterator& it, const Iterator& last, renamer& r);

expr parse_factor(Iterator& it, const Iterator& last, renamer& r)
{
  if (it == last) {
    throw __LINE__;
  }

  if (*it == '~') {
    ++it;
    return ~parse_factor(it, last, r);
  } else if (*it == '(') {
    ++it;
    const expr e = parse_expr(it, last, r);
    if (*it != ')') {
      throw __LINE__;
    }
    ++it;
    return e;
  } else if (isalpha(*it)) {
    string var;
    while (it != last && isalpha(*it)) {
      var += *it;
      ++it;
    }
    expr e;
    e.lit = r(var)<<1;
    return e;
  } else {
    throw __LINE__;
  }
}

expr parse_expr(Iterator& it, const Iterator& last, renamer& r)
{
  if (it == last) {
    throw __LINE__;
  }
  expr e = parse_factor(it, last, r);
  if (it != last && (*it == '&' || *it == '|')) {
    int op = -1;
    if (*it == '&') {
      op = 0;
    } else if (*it == '|') {
      op = 1;
    } else {
      throw __LINE__;
    }
    if (!e.lit_p()) {
      throw __LINE__;
    }
    ++it;
    const expr f = parse_factor(it, last, r);
    if (!f.lit_p()) {
      throw __LINE__;
    }
    e.op = op;
    e.lhs = e.lit;
    e.rhs = f.lit;
  }
  return e;
}

void scc_visit(const vector<vector<int> >& g, int v, vector<int>& scc_map, int& scc_size,/*{{{*/
        stack<int>& stk, vector<bool>& in_stk, vector<int>& low, vector<int>& num, int& time)
{
  low[v] = num[v] = ++time;
  stk.push(v);
  in_stk[v] = true;
  for (vector<int>::const_iterator it(g[v].begin()); it != g[v].end(); ++it) {
    const int u = *it;
    if (num[u] == 0) {
      scc_visit(g, u, scc_map, scc_size, stk, in_stk, low, num, time);
      low[v] = min(low[v], low[u]);
    } else if (in_stk[u]) {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) {
    for (;;) {
      const int u = stk.top();
      stk.pop();
      in_stk[u] = false;
      scc_map[u] = scc_size;
      if (u == v) {
        break;
      }
    }
    ++scc_size;
  }
}/*}}}*/

// O(V+E)
pair<vector<int>,int> strongly_connected_components(const vector<vector<int> >& g)/*{{{*/
{
  const int N = g.size();
  vector<int> num(N), low(N);
  stack<int> stk;
  vector<bool> in_stk(N, false);
  int time = 0;
  vector<int> scc_map(N);
  int scc_size = 0;
  for (int v = 0; v < N; v++) {
    if (num[v] == 0) {
      scc_visit(g, v, scc_map, scc_size, stk, in_stk, low, num, time);
    }
  }
  return make_pair(scc_map, scc_size);
}/*}}}*/

bool two_sat(const vector<vector<int> >& g)
{
  const int N = g.size()/2;
  const pair<vector<int>,int> p = strongly_connected_components(g);
  const vector<int>& scc_map = p.first;
  for (int i = 0; i < N; i++) {
    if (scc_map[i<<1] == scc_map[(i<<1)|1]) {
      return false;
    }
  }
  return true;
}

bool solve(const vector<expr>& v, int M)
{
  vector<vector<int> > g(2*M);
  vector<int> lits(M, -1);
  for (vector<expr>::const_iterator it = v.begin(); it != v.end(); ++it) {
    if (it->lit_p()) {
      g[it->lit ^ 1].push_back(it->lit);
    } else if (it->and_p()) {
      g[it->lhs ^ 1].push_back(it->lhs);
      g[it->rhs ^ 1].push_back(it->rhs);
    } else if (it->or_p()) {
      g[it->lhs ^ 1].push_back(it->rhs);
      g[it->rhs ^ 1].push_back(it->lhs);
    } else {
      throw __LINE__;
    }
  }
  return two_sat(g);
}

string line;

int main() try
{
  int N, M;
  cin >> N >> M;

  renamer r;
  vector<expr> v;
  for (int i = 0; i < N; i++) {
    cin >> line;
    Iterator it = line.begin();
    v.push_back(parse_expr(it, line.end(), r));
    if (*it != ';') {
      throw __LINE__;
    }
  }

  cout << (solve(v, M) ? "accept" : "reject") << endl;
  return 0;
} catch (int lineno) {
  cerr << line << endl;
  cerr << "EXCEPTION at line " << lineno << endl;
}
