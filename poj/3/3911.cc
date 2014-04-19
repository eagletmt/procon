#include <iostream>
using namespace std;

int main()
{
  long long N, C;
  while (cin >> N >> C) {
    if (N == 0) {
      cout << 0 << endl;
    } else {
      long long t = C / N / 2LL;
      long long m = t*(C-t*N);
      long long T = t;

      ++t;
      if (t*(C-t*N) > m) {
        T = t;
      }
      cout << T << endl;
    }
  }
  return 0;
}