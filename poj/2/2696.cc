#include <iostream>
#include <algorithm>
using namespace std;

int mod(int p, int m)
{
  return (p % m + m) % m;
}

struct phi {
  int memo[1001];
  int d, e, f, g, h;

  phi(int a, int b, int c, int d, int e, int f, int g, int h)
    : d(d), e(e), f(f), g(g), h(h)
  {
    fill_n(memo, sizeof memo/sizeof *memo, -1);
    memo[0] = a;
    memo[1] = b;
    memo[2] = c;
  }

  int operator()(int i)
  {
    if (memo[i] != -1) {
      return memo[i];
    } else {
      if (i % 2 == 1) {
        return memo[i] = mod(d*this->operator()(i-1) + e*this->operator()(i-2) - f*this->operator()(i-3), g);
      } else {
        return memo[i] = mod(f*this->operator()(i-1) - d*this->operator()(i-2) + e*this->operator()(i-3), h);
      }
    }
  }
};

int main()
{
  int n;
  cin >> n;
  while (n--) {
    int a, b, c, d, e, f, g, h, i;
    cin >> a >> b >> c >> d >> e >> f >> g >> h >> i;
    phi p(a, b, c, d, e, f, g, h);
    cout << p(i) << endl;
  }
  return 0;
}
