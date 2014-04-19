#include <iostream>
using namespace std;

int clockwise(int a, int b)
{
  if (a >= b) {
    return a - b;
  } else {
    return a + (40 - b);
  }
}

int counterclockwise(int a, int b)
{
  if (a <= b) {
    return b - a;
  } else {
    return (40 - a) + b;
  }
}

int main()
{
  int a, b, c, d;
  while (cin >> a >> b >> c >> d
      && !(a == 0 && b == 0 && c == 0 && d == 0)) {
    int x = 80;
    x += clockwise(a, b);
    x += 40;
    x += counterclockwise(b, c);
    x += clockwise(c, d);
    cout << x*(360/40) << endl;
  }
  return 0;
}
