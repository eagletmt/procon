#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int Z;
  cin >> Z;

  while (Z-- > 0) {
    int M, H;
    cin >> M >> H;

    long long sum = 0;
    while (H-- > 0) {
      long long a, b;
      cin >> a >> b;

      long long ret = 1;
      while (b > 0) {
        if (b & 1) {
          ret = (ret * a) % M;
        }
        b >>= 1;
        a = (a*a) % M;
      }
      sum = (sum + ret) % M;
    }
    cout << sum << endl;
  }
  return 0;
}
