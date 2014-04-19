#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
using namespace std;

double solve(int n, int s, int t, int b)
{
  vector<double> probs(9, 0.0);
  probs[s] = 1.0;

  for (int i = 0; i < n; i++) {
    vector<double> next(9, 0.0);
    for (int j = 0; j < 9; j++) {
      for (int d = 0; d < 4; d++) {
        static const int di[] = {-1, 1, 0, 0};
        static const int dj[] = {0, 0, 1, -1};
        const int k = (j / 3) + di[d];
        const int l = (j % 3) + dj[d];
        if (k < 0 || 3 <= k || l < 0 || 3 <= l || 3*k+l == b) {
          next[j] += probs[j] * 0.25;
        } else {
          next[3*k+l] += probs[j] * 0.25;
        }
      }
    }
    probs = next;
  }

  return probs[t];
}

int main()
{
  int n;
  while (cin >> n && n != 0) {
    char s, t, b;
    cin >> s >> t >> b;
    printf("%.8f\n",  solve(n, s-'A', t-'A', b-'A'));
  }
  return 0;
}
