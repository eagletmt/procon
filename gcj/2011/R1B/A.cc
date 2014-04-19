#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; ++Ti) {
    cout << "Case #" << Ti << ":" << endl;

    int N;
    cin >> N;
    vector<string> scores(N);
    for (int i = 0; i < N; i++) {
      cin >> scores[i];
    }

    vector<double> wp(N);
    for (int i = 0; i < N; i++) {
      int c = 0, n = 0;
      for (int j = 0; j < N; j++) {
        if (scores[i][j] != '.') {
          ++n;
        }
        if (scores[i][j] == '1') {
          ++c;
        }
      }
      wp[i] = static_cast<double>(c) / n;
    }

    vector<double> owp(N);
    for (int i = 0; i < N; i++) {
      double s = 0.0;
      int m = 0;
      for (int j = 0; j < N; j++) {
        if (j == i || scores[j][i] == '.') {
          continue;
        }
        ++m;
        int c = 0, n = 0;
        for (int k = 0; k < N; k++) {
          if (j != k && k != i) {
            if (scores[j][k] != '.') {
              ++n;
            }
            if (scores[j][k] == '1') {
              ++c;
            }
          }
        }
        s += double(c)/n;
      }
      owp[i] = s / m;
    }

    vector<double> oowp(N);
    for (int i = 0; i < N; i++) {
      double s = 0.0;
      int m = 0;
      for (int j = 0; j < N; j++) {
        if (i != j && scores[i][j] != '.') {
          s += owp[j];
          ++m;
        }
      }
      oowp[i] = s / m;
    }

    for (int i = 0; i < N; i++) {
      printf("%.6f\n", 0.25*wp[i] + 0.50*owp[i] + 0.25*oowp[i]);
    }
  }
  return 0;
}
