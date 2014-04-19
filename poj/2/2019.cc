#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N, B, K;
  scanf("%d %d %d", &N, &B, &K);
  static int matrix[250][250];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      scanf("%d", &matrix[i][j]);
    }
  }

  static int row_l[250][250], row_u[250][250];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= N-B; j++) {
      row_l[i][j] = row_u[i][j] = matrix[i][j];
      for (int k = 0; k < B; k++) {
        row_l[i][j] = min(row_l[i][j], matrix[i][j+k]);
        row_u[i][j] = max(row_u[i][j], matrix[i][j+k]);
      }
    }
  }
  static int ls[250][250], us[250][250];
  for (int i = 0; i <= N-B; i++) {
    for (int j = 0; j <= N-B; j++) {
      ls[i][j] = us[i][j] = matrix[i][j];
      for (int k = 0; k < B; k++) {
        ls[i][j] = min(ls[i][j], row_l[i+k][j]);
        us[i][j] = max(us[i][j], row_u[i+k][j]);
      }
    }
  }

  for (int i = 0; i < K; i++) {
    int j, k;
    scanf("%d %d", &j, &k);
    --j;  --k;
    printf("%d\n", us[j][k] - ls[j][k]);
  }
  return 0;
}