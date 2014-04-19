#include <iostream>
using namespace std;

int main()
{
  int N;
  cin >> N;
  for (int i = 1; i <= N; i++) {
    int a, b;
    cin >> a >> b;

    int left = 0, right = 0;
    while (a != 1 && b != 1) {
      if (a > b) {
        left += a / b;
        a %= b;
      } else {
        right += b / a;
        b %= a;
      }
    }
    if (a == 1) {
      right += b-1;
    } else {
      left += a-1;
    }

    cout << "Scenario #" << i << ':' << endl;
    cout << left << ' ' << right << endl;
    cout << endl;
  }
  return 0;
}
