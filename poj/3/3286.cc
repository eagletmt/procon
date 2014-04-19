#include <iostream>
using namespace std;

long long count(long long n)
{
  long long ans = 1LL;
  long long d = 1LL;
  long long acc = 0LL;
  while (n > 0) {
    const long long r = n % 10;
    n /= 10;
    if (r == 0) {
      ans += (n-1)*d+acc+1;
    } else {
      ans += n*d;
    }
    acc += r*d;
    d *= 10;
  }
  return ans;
}

long long zeros(long long n)
{
  int ans = 0;
  do {
    const long long r = n % 10;
    if (r == 0) {
      ++ans;
    }
    n /= 10;
  } while (n > 0);
  return ans;
}

int main()
{
  long long m, n;
  while (cin >> m >> n && m != -1) {
    cout << count(n)-count(m)+zeros(m) << endl;
  }
  return 0;
}
