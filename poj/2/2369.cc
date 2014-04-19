#include <iostream>
#include <vector>
using namespace std;

int period(const int n, const vector<int>& v)
{
  int c = 1;
  for (int i = n; v[i] != n; i = v[i], ++c);
  return c;
}

unsigned long long gcd(unsigned long long x, unsigned long long y)
{
  if (x < y) {
    swap(x, y);
  }
  for (unsigned long long r = x % y; r != 0; x = y, y = r, r = x % y);
  return y;
}

unsigned long long lcm(unsigned long long x, unsigned long long y)
{
  return x*y / gcd(x, y);
}

int main()
{
  int N;
  cin >> N;
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
    --v[i];
  }

  unsigned long long ans = 1;
  for (vector<int>::const_iterator it(v.begin()); it != v.end(); ++it) {
    const int n = period(*it, v);
    ans = lcm(ans, n);
  }
  cout << ans << endl;
  return 0;
}