#include <iostream>
using namespace std;

int main()
{
  int A, B;
  while (cin >> A >> B && A != 0) {
    int c = B - A;
    const int c1000 = c / 1000;
    c %= 1000;
    const int c500 = c / 500;
    c %= 500;
    cout << c/100 << ' ' << c500 << ' ' << c1000 << endl;
  }
  return 0;
}
