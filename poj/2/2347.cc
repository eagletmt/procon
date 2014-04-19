#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
using namespace std;

long long gcd(long long a, long long b)/*{{{*/
{
  if (a < b) {
    swap(a, b);
  }
  long long r;
  while ((r = a % b) != 0LL) {
    a = b;
    b = r;
  }
  return b;
}/*}}}*/

struct ratio/*{{{*/
{
  long long n, d;
  ratio() : n(0), d(1) {}
  ratio(long long a) : n(a), d(1) {}
  ratio(long long a, long long b) : n(a), d(b) { normalize(); }

  void normalize()
  {
    if (n == 0) {
      d = 1;
    } else {
      const long long g = gcd(n, d);
      n /= g;
      d /= g;
      if (d < 0) {
        n = -n;
        d = -d;
      }
    }
  }

  ratio inverse() const { return ratio(d, n); }

  bool operator==(const ratio& r) const { return n == r.n && d == r.d; }
  bool operator==(int x) const { return d == 1 && n == x; }
  bool operator!=(int x) const { return !(*this == x); }
  ratio operator-() const { return ratio(-n, d); }

  ratio& operator-=(const ratio& r)
  {
    const long long dd = d * r.d;
    const long long nn = n*r.d - r.n*d;
    d = dd;
    n = nn;
    normalize();
    return *this;
  }
  ratio operator*(const ratio& r) const { return ratio(n * r.n, d * r.d); }
};/*}}}*/

ostream& operator<<(ostream& os, const ratio& r)
{
  if (r.d == 1) {
    return os << r.n;
  } else {
    return os << r.n << '/' << r.d;
  }
}

template <class T>
void gaussian_elimination(vector<vector<T> >& a, vector<T>& b)/*{{{*/
{
  const int N = a.size();
  const int M = a[0].size();
  // assert(N >= M)

  for (int i = 0, p = 0; i < M; i++, p++) {
    int q;
    for (q = p; q < N && a[q][i] == 0; q++);
    if (q == N) {
      --p;
      continue;
    }
    swap(a[i], a[q]);
    swap(b[i], b[q]);

    const T r = a[i][i].inverse();
    for (int k = i; k < M; k++) {
      a[i][k] = a[i][k] * r;
    }
    b[i] = b[i] * r;

    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const T t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] -= t * a[i][k];
      }
      b[j] -= t * b[i];
    }
  }
}/*}}}*/

void parse(vector<ratio>& a, ratio& b, const string& s)
{
  int ax = 0, ay = 0, bb = 0;
  int sign = 1;
  char op = '+';
  istringstream iss(s);
  for (string t; iss >> t;) {
    if (t == "=") {
      sign *= -1;
      op = '+';
    } else if (t == "+") {
      op = '+';
    } else if (t == "-") {
      op = '-';
    } else {
      int c = 1;
      int minus = 1;
      string::const_iterator it = t.begin();
      if (*it == '-') {
        minus = -minus;
        ++it;
      }
      if (isdigit(*it)) {
        c = 0;
        for (; it != t.end() && isdigit(*it); ++it) {
          c = 10*c + (*it-'0');
        }
      }

      if (op == '-') {
        minus = -minus;
      }
      const int val = sign * minus * c;
      if (it == t.end()) {
        bb += val;
      } else {
        if (*it == 'x') {
          ax += val;
        } else if (*it == 'y') {
          ay += val;
        } else {
          throw "unknown character";
        }
        ++it;
        if (it != t.end()) {
          throw "trailing character";
        }
      }
    }
  }
  a[0] = ax;
  a[1] = ay;
  b = -bb;
}

int main()
{
  int T;
  cin >> T;
  cin.ignore();
  bool first = true;
  while (T-- > 0) {
    if (!first) {
      cout << endl;
    }
    first = false;
    string s1, s2;
    getline(cin, s1);
    getline(cin, s2);
    string empty;
    getline(cin, empty);

    vector<vector<ratio> > a(2, vector<ratio>(2));
    vector<ratio> b(2);
    parse(a[0], b[0], s1);
    parse(a[1], b[1], s2);
    gaussian_elimination(a, b);

    bool invalid = false;
    for (int i = 0; i < 2; i++) {
      //cerr << a[i][0] << " " << a[i][1] << " = " << b[i] << endl;
      if (a[i][i] == 0 && b[i] != 0) {
        // no solutions
        invalid = true;
      }
      if (a[i][1-i] != 0) {
        // infinite solutions
        invalid = true;
      }
    }
    for (int i = 0; i < 2; i++) {
      if (invalid || a[i][i] == 0) {
        cout << "don't know" << endl;
      } else {
        if (a[i][i] != 1) {
          throw "a";
        }
        cout << b[i] << endl;
      }
    }
  }
  return 0;
}