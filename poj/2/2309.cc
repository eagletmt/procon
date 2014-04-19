#include <iostream>
using namespace std;

int main(void)
{
  int N;
  cin >> N;
  while (N--) {
    int x;
    cin >> x;

    int r = x;
    int b = 1;
    while ((x & b) == 0) {
      r |= b;
      b <<= 1;
    }
    const int l = (x & ~b) + 1;
    cout << l << ' ' << r << endl;
  }
  return 0;
}
