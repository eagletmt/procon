#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
using namespace std;

int main()
{
  int N, T, L, B;
  while (cin >> N >> T >> L >> B && N != 0) {
    set<int> lose, back;
    for (int i = 0; i < L; i++) {
      int x;
      cin >> x;
      lose.insert(x);
    }
    for (int i = 0; i < B; i++) {
      int x;
      cin >> x;
      back.insert(x);
    }

    vector<vector<double> > prob(T+1, vector<double>(N, 0.0));
    prob[0][0] = 1.0;
    double ans = 0.0;
    for (int t = 0; t < T; t++) {
      for (int i = 0; i < N; i++) {
        for (int dice = 1; dice <= 6; dice++) {
          int next = i + dice;
          if (next == N) {
            ans += prob[t][i]/6.0;
          } else {
            if (next > N) {
              next = N-(next-N);
            }
            if (lose.count(next)) {
              if (t+2 < T+1) {
                prob[t+2][next] += prob[t][i]/6.0;
              }
            } else if (back.count(next)) {
              prob[t+1][0] += prob[t][i]/6.0;
            } else {
              prob[t+1][next] += prob[t][i]/6.0;
            }
          }
        }
      }
    }
    printf("%.6f\n", ans);
  }
  return 0;
}
