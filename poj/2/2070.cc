#include <iostream>
using namespace std;
int main()
{
  double a, b, c;
  while (cin >> a >> b >> c && a > 1e-9 && b > 1e-9 && c > 1e-9) {
    const bool w = a <= 4.5 && b >= 150 && c >= 200;
    const bool l = a <= 6.0 && b >= 300 && c >= 500;
    const bool q = a <= 5 && b >= 200 && c >= 300;
    if (w) {
      cout << "Wide Receiver";
      if (l) {
        cout << " Lineman";
      }
      if (q) {
        cout << " Quarterback";
      }
    } else if (l) {
      cout << "Lineman";
      if (q) {
        cout << " Quarterback";
      }
    } else if (q) {
      cout << "Quarterback";
    } else {
      cout << "No positions";
    }
    cout << endl;
  }
  return 0;
}
