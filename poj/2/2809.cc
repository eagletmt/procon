#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

int pow(int x, int n)
{
  if (n == 0) {
    return 1;
  } else if (n & 1) {
    return x * pow(x, n-1);
  } else {
    const int t = pow(x, n>>1);
    return t*t;
  }
}

struct term
{
  int coeff, power;
  string var;

  void differentiate()
  {
    coeff *= power;
    --power;
  }

  int eval(int x) const
  {
    if (power < 0) {
      return 0;
    }
    return coeff * pow(x, power);
  }
};

typedef string::const_iterator Iterator;

term parse_term(Iterator& it, const Iterator& last)
{
  bool neg = false;
  if (*it == '-') {
    neg = true;
    ++it;
  }
  term t;
  if (isdigit(*it)) {
    t.coeff = *it - '0';
    ++it;
  } else {
    t.coeff = 1;
  }
  if (neg) {
    t.coeff = -t.coeff;
  }
  if (it == last || *it != 'x') {
    t.power = 0;
    return t;
  }
  t.var = *it;
  ++it;
  if (it != last && *it == '^') {
    ++it;
    t.power = *it - '0';
    ++it;
  } else {
    t.power = 1;
  }
  return t;
}

vector<term> parse_expr(Iterator& it, const Iterator& last)
{
  vector<term> e;
  e.push_back(parse_term(it, last));
  while (it != last && (*it == '+' || *it == '-')) {
    if (*it == '+') {
      ++it;
    }
    e.push_back(parse_term(it, last));
  }
  return e;
}

void print_expr(const vector<term>& expr)
{
  if (expr.front().power < 0) {
    cout << expr.front().coeff << endl;
    return;
  }
  for (vector<term>::const_iterator it = expr.begin(); it != expr.end(); ++it) {
    if (it->power < 0) {
      continue;
    }
    if (it != expr.begin() && it->coeff >= 0) {
      cout << "+";
    }

    if (it->power == 0) {
      cout << it->coeff;
    } else {
      if (it->coeff != 1) {
        cout << it->coeff;
      }
      cout << it->var;
      if (it->power != 1) {
        cout << "^" << it->power;
      }
    }
  }
  cout << endl;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int x;
    string s;
    cin >> x >> s;

    cout << "POLYNOMIAL " << Ti << endl;
    cout << s << endl;

    Iterator first = s.begin(), last = s.end();
    vector<term> expr = parse_expr(first, last);
    for (vector<term>::iterator it = expr.begin(); it != expr.end(); ++it) {
      it->differentiate();
    }
    print_expr(expr);
    for (vector<term>::iterator it = expr.begin(); it != expr.end(); ++it) {
      ostringstream oss;
      oss << "(" << x << ")";
      it->var = oss.str();
    }
    print_expr(expr);

    int acc = 0;
    for (vector<term>::const_iterator it = expr.begin(); it != expr.end(); ++it) {
      if (it->power < 0) {
        continue;
      }
      const int n = it->eval(x);
      if (it != expr.begin() && n >= 0) {
        cout << "+";
      }
      cout << n;
      acc += n;
    }
    if (expr.front().power < 0) {
      cout << 0;
    }
    cout << endl;

    cout << acc << endl;
  }
  return 0;
}