#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N, S;
  cin >> N >> S;

  vector<vector<int> > v(N, vector<int>(N, 0));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= i; j++) {
      v[i][j] = S;
      S = S == 9 ? 1 : S+1;
    }
  }

  for (int i = 0; i < N;  i++) {
    for (int j = 0; j < N; j++) {
      if (j != 0) {
        cout << ' ';
      }
      if (v[j][i] == 0) {
        cout << ' ';
      } else {
        cout << v[j][i];
      }
    }
    cout << endl;
  }
  return 0;
}
