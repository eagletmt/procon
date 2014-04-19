#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int c[9];
  while (cin >> c[0]) {
    for (int i = 1; i < 9; i++) {
      cin >> c[i];
    }

    bool first = true;
    for (int i = 0; i < 9; i++) {
      if (c[i] != 0) {
        if (c[i] < 0) {
          if (first) {
            cout << "-";
          } else {
            cout << " - ";
          }
        } else {
          if (!first) {
            cout << " + ";
          }
        }
        first = false;
        const int x = abs(c[i]);
        if (x != 1 || i == 8) {
          cout << x;
        }
        if (i < 8) {
          cout << "x";
        }
        if (i < 7) {
          cout << "^" << (8-i);
        }
      }
    }
    if (first) {
      cout << 0;
    }
    cout << endl;
  }
  return 0;
}