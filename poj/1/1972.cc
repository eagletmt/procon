#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t--) {
    int n;
    cin >> n;
    vector<vector<int> > dices(n, vector<int>(6));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < 6; j++) {
        cin >> dices[i][j];
      }
    }

    int ans = 0;
    for (int i = 0; i < 3; i++) {
      static int rev[] = {5, 3, 4, 1, 2, 0};
      /* define initial top */
      int top = dices[0][i];
      for (int j = 0; j < 6; j++) {
        if (j == i || j == rev[i]) {
          continue;
        }
        /* define start plane */
        int sum = dices[0][j];
        for (int k = 1; k < n; k++) {
          int m = 0;
          int next_top;
          for (int l = 0; l < 6; l++) {
            if (dices[k][l] == top) {
              next_top = dices[k][rev[l]];
            } else if (dices[k][rev[l]] != top) {
              m = max(m, dices[k][l]);
            }
          }
          sum += m;
          top = next_top;
        }
        ans = max(ans, sum);
      }
    }
    cout << ans << endl;
  }

  return 0;
}
