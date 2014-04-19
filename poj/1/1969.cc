#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int term;
  while (cin >> term) {
    int a = (1 + sqrt(1 + 8*(term-1))) / 2.0;
    int b = term - (1+a*(a-1)/2);
    if (a % 2 == 0) {
      cout << "TERM " << term << " IS " << b+1 << '/' << a-b << endl;
    } else {
      cout << "TERM " << term << " IS " << a-b << '/' << b+1 << endl;
    }
  }
  return 0;
}