#include <iostream>
#include <cstdio>
#include <vector>
#include <cmath>
using namespace std;

int main()
{
  int N, M, K;
  while (cin >> N >> M >> K && N != 0) {
    vector<vector<int> > dp(N, vector<int>(N*M+1, 0));
    for (int j = 1; j <= M; j++) {
      dp[0][j] = 1;
    }
    for (int i = 1; i < N; i++) {
      for (int j = 1; j <= N*M; j++) {
        for (int k = 1; k <= M && j-k >= 0; k++) {
          dp[i][j] += dp[i-1][j-k];
        }
      }
    }

    int n = 0;
    for (int j = 1; j <= N*M; j++) {
      n += dp[N-1][j] * max(1, j-K);
    }
    printf("%.8f\n", double(n)/pow(double(M), double(N)));
  }
  return 0;
}
