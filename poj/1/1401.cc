#include <iostream>
using namespace std;

int main(void)
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    int n2 = 0;
    for (int base = 2; base <= N; base *= 2) {
      n2 += N/base;
    }
    int n5 = 0;
    for (int base = 5; base <= N; base *= 5) {
      n5 += N/base;
    }
    cout << min(n2, n5) << endl;
  }
  return 0;
}
