#include <iostream>
#include <vector>
using namespace std;

int rev(int n)
{
  int r = 0;
  while (n > 0) {
    r = 10*r + n%10;
    n /= 10;
  }
  return r;
}

int main(void)
{
  int N;
  cin >> N;
  while (N-->0) {
    int a, b;
    cin >> a >> b;
    cout << rev(rev(a) + rev(b)) << endl;
  }
  return 0;
}
