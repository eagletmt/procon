#include <iostream>
using namespace std;

int main()
{
  int p, e, i, d;
  for (int T = 1; cin >> p >> e >> i >> d && p != -1; ++T) {
    int c;
    for (c = d; (c-p)%23 != 0 || (c-e)%28 != 0 || (c-i)%33 != 0; ++c);
    c -= d;
    if (c == 0) {
      c = 21252;
    }
    cout << "Case " << T << ": the next triple peak occurs in " << c << " days." << endl;
  }
  return 0;
}