#include <iostream>
using namespace std;

int main()
{
  int H, U, D, F;
  while (cin >> H >> U >> D >> F && H != 0) {
    const int r = U * F;
    H *= 100;
    D *= 100;

    bool success;
    int height = 0, speed = 100*U;
    int day = 1;
    for (;; day++) {
      height += speed;
      speed = max(0, speed - r);
      if (height > H) {
        success = true;
        break;
      }
      height -= D;
      if (height < 0) {
        success = false;
        break;
      }
    }
    if (success) {
      cout << "success on day " << day << endl;
    } else {
      cout << "failure on day " << day << endl;
    }
  }
  return 0;
}