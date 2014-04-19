#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int P, N;
    scanf("%d %d", &P, &N);
    vector<vector<int> > dist(N, vector<int>(N, 10000000));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        scanf("%d", &dist[i][j]);
      }
    }

    for (int k = 0; k < N; k++) {
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          if (dist[i][k] > 0 && dist[k][j] > 0) {
            if (dist[i][j] == -1) {
              dist[i][j] = dist[i][k] + dist[k][j];
            } else {
              dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
            }
          }
        }
      }
    }

    vector<int> v;
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (dist[i][j] > 0) {
          v.push_back(dist[i][j]);
        }
      }
    }
    const int M = N*(N-1)*P;
    const int K = M/100 + (M%100 != 0);
    sort(v.begin(), v.end());
    printf("Scenario #%d:\n%d\n\n", Ti, v[K-1]);
  }
  return 0;
}