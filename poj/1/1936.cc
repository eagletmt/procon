#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  string a, b;

  while (cin >> a >> b) {
    const int N = a.size(), M = b.size();
    vector<vector<int> > lcs(N+1, vector<int>(M+1, 0));
    for (int i = 1; i <= N; i++) {
      for (int j = 1; j <= M; j++) {
        if (a[i-1] == b[j-1]) {
          lcs[i][j] = max(lcs[i-1][j-1]+1, max(lcs[i-1][j], lcs[i][j-1]));
        } else {
          lcs[i][j] = max(lcs[i-1][j-1], max(lcs[i-1][j], lcs[i][j-1]));
        }
      }
    }
    cout << (lcs[N][M] == N ? "Yes" : "No") << endl;
  }
  return 0;
}
