#include <iostream>
using namespace std;

int main(void)
{
  int R, M, Y;
  cin >> R >> M >> Y;

  double d = M;
  while (Y-->0) {
    d += d*R*1e-2;
  }
  cout << int(d) << endl;

  return 0;
}