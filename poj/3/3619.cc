#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  int N, K;
  cin >> N >> K;

  while (K-- > 0) {
    int s, t, r;
    cin >> s >> t >> r;
    int a = N / (s*t);
    int b = N % (s*t);
    cout << a*t + (b == 0 ? a-1 : a)*r + ceil(b/double(s)) << endl;
  }
  return 0;
}
