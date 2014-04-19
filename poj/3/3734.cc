#include <iostream>
using namespace std;
static const int M = 10007;

int powmod(int x, int e, int m)
{
  if (e == 0) {
    return 1;
  } else if (e % 2 == 0) {
    const int y = powmod(x, e/2, m);
    return (y * y) % m;
  } else {
    return (x * powmod(x, e-1, m)) % m;
  }
}

int main()
{
  int T;
  cin >> T;
  while (T--) {
    int n;
    cin >> n;
    n = (n-1) % (M-1);
    cout << (powmod(2, n, M) + powmod(4, n, M)) % M << endl;
  }
  return 0;
}
