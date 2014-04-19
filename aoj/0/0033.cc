#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N;
  cin >> N;
  while (N-- > 0) {
    vector<int> balls(10);
    for (int i = 0; i < 10; i++) {
      cin >> balls[i];
    }

    for (int i = 0; i < 1024; i++) {
      int b = 0, c = 0;
      int j;
      for (j = 0; j < 10; j++) {
        if (i & (1<<j)) {
          if (b < balls[j]) {
            b = balls[j];
          } else {
            break;
          }
        } else {
          if (c < balls[j]) {
            c = balls[j];
          } else {
            break;
          }
        }
      }
      if (j == 10) {
        cout << "YES" << endl;
        goto NEXT;
      }
    }
    cout << "NO" << endl;
NEXT:
    ;
  }
  return 0;
}
