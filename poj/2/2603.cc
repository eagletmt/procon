#include <iostream>
using namespace std;

int main()
{
  static unsigned c[10000];

  for (int i = 0; i < 10; i++) {
    int x;
    cin >> x;
    for (int j = 2; j <= x; j++) {
      while (x % j == 0) {
        ++c[j];
        x /= j;
      }
    }
  }
  unsigned ans = 1;
  for (int i = 0; i < 10000; i++) {
    ans = (ans * (c[i]+1)) % 10;
  }
  cout << ans << endl;
  return 0;
}
