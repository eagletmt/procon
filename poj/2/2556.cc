#include <iostream>
using namespace std;

int main()
{
  string s;
  while (cin >> s) {
    cout << "300 420 moveto" << endl;
    cout << "310 420 lineto" << endl;
    int x = 310;
    int y = 420;
    int d = 0;
    for (string::const_iterator it(s.begin()); it != s.end(); ++it) {
      static const int dx[] = {10, 0, -10, 0};
      static const int dy[] = {0, -10, 0, 10};
      if (*it == 'A') {
        d = (d + 1) % 4;
      } else {
        d = (d + 3) % 4;
      }
      x += dx[d];
      y += dy[d];
      cout << x << ' ' << y << " lineto" << endl;
    }
    cout << "stroke" << endl;
    cout << "showpage" << endl;
  }
  return 0;
}
