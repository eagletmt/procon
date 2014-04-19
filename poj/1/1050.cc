#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<vector<int> > matrix(N, vector<int>(N));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      cin >> matrix[i][j];
    }
  }

  int ans = numeric_limits<int>::min();
  for (int i = 0; i < N; i++) {
    vector<int> v(N, 0);
    for (int j = i; j < N; j++) {
      for (int k = 0; k < N; k++) {
        v[k] += matrix[j][k];
      }

      int x = 0, m = numeric_limits<int>::min();
      for (int l = 0; l < N; l++) {
        x = max(x+v[l], v[l]);
        m = max(m, x);
      }
      ans = max(ans, m);
    }
  }
  cout << ans << endl;
  return 0;
}
