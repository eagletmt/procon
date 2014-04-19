#include <iostream>
using namespace std;

int f(int x)
{
  static int a[30000000];
  return x;
}

int main()
{
  int a, b;
  cin >> a >> b;
  cout << f(a+b) << endl;
  return 0;
}
