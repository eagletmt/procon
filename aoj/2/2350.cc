#include <iostream>
using namespace std;

int solve(const int *a, const int *b, int s)
{
  int c[10] = {0};
  int borrow = 0;
  for (int i = 0; i < 10; i++) {
    if (a[i] - borrow >= b[i]) {
      c[i] = a[i] - borrow - b[i];
      borrow = 0;
    } else {
      c[i] = a[i] - borrow + 10 - b[i];
      if (s & (1<<i)) {
        borrow = 0;
      } else {
        borrow = 1;
      }
    }
  }
  int n = 0;
  for (int i = 9; i >= 0; i--) {
    n = 10*n + c[i];
  }
  return n;
}

int main()
{
  int A, B, K;
  cin >> A >> B >> K;
  int a[10], b[10];
  for (int i = 0; i < 10; i++) {
    a[i] = A%10;
    b[i] = B%10;
    A /= 10;
    B /= 10;
  }

  int ans = 0;
  for (int s = 0; s < (1<<9); s++) {
    if (__builtin_popcount(s) <= K) {
      ans = max(ans, solve(a, b, s));
    }
  }
  cout << ans << endl;
  return 0;
}
