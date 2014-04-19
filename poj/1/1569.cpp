#include <iostream>
#include <complex>
#include <map>

using namespace std;

typedef complex<double> P;
double EPS = 1e-8;

double area(P a, P b, P c)
{
  b -= a;
  c -= a;
  return abs(real(b)*imag(c) - imag(b)*real(c))/2.0;
}

typedef map<char, P>::const_iterator m_iterator;

bool valid(map<char, P> m, m_iterator a, m_iterator b, m_iterator c)
{
  for (m_iterator i(m.begin()); i != m.end(); ++i) {
    if (a->first == i->first || b->first == i->first || c->first == i->first) {
      continue;
    }
    P x = a->second, y = b->second, z = c->second, w = i->second;
    if (area(x, y, w) + area(y, z, w) + area(z, x, w) - area(x, y, z) < EPS) {
      return false;
    }
  }
  return true;
}

string solve(map<char, P> m)
{
  string ret("AAA");
  double cur_max = 0.0;
  for (m_iterator i(m.begin()); i != m.end(); ++i) {
    m_iterator j(i);
    ++j;
    for (; j != m.end(); ++j) {
      m_iterator k(j);
      ++k;
      for (; k != m.end(); ++k) {
        if (valid(m, i, j, k)) {
          double v = area(i->second, j->second, k->second);
          if (v > cur_max) {
            cur_max = v;
            ret[0] = i->first;
            ret[1] = j->first;
            ret[2] = k->first;
          }
        }
      }
    }
  }
  return ret;
}

int main(void)
{
  int n = -1;
  while (true) {
    cin >> n;
    if (n == 0) {
      break;
    }

    map<char, P> m;
    for (int i = 0; i < n; i++) {
      char k;
      double x, y;
      cin >> k >> x >> y;
      m.insert(make_pair(k, P(x, y)));
    }
    cout << solve(m) << endl;
  }
  return 0;
}
