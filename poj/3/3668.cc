#include <iostream>
#include <vector>
#include <set>
#include <iterator>
#include <cstdlib>
using namespace std;

int gcd(int a, int b)
{
  if (a < b) {
    swap(a, b);
  }
  while (int r = a%b) {
    a = b;
    b = r;
  }
  return b;
}

struct Ratio {
  int n, d;
  Ratio(int a, int b)
  {
    if (a == 0) {
      n = 0;
      d = 1;
    } else {
      n = abs(a);
      d = abs(b);
      const int g = gcd(n, d);
      n /= g;
      d /= g;
      if (a*b < 0) {
        n = -n;
      }
    }
  }
  bool operator<(const Ratio& rhs) const
  {
    return n*rhs.d < rhs.n*d;
  }
};

ostream& operator<<(ostream& os, const Ratio& r)
{
  return os << r.n << '/' << r.d;
}

int main()
{
  int N;
  cin >> N;
  vector<pair<int,int> > v(N);
  for (int i = 0; i < N; i++) {
    int x, y;
    cin >> x >> y;
    v[i] = make_pair(x, y);
  }
  set<Ratio> s;
  bool b = false;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      const int x = v[i].first - v[j].first;
      const int y = v[i].second - v[j].second;
      if (x == 0) {
        b = true;
      } else {
        s.insert(Ratio(y, x));
      }
    }
  }
  cout << s.size() + b << endl;
  return 0;
}
