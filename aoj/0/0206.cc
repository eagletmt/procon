#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int L;
  while (cin >> L && L != 0) {
    vector<int> ds(12);
    for (int i = 0; i < 12; i++) {
      int M, N;
      cin >> M >> N;
      ds[i] = M-N;
    }

    int s = 0;
    int ans = 0;
    for (int i = 0; i < 12; i++) {
      s += ds[i];
      if (s >= L) {
        ans = i+1;
        break;
      }
    }
    if (ans == 0) {
      cout << "NA" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
