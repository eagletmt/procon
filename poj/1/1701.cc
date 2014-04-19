#include <cstdio>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int M, a, b;
    scanf("%d %d %d", &M, &a, &b);
    static const int K = 10000;
    static int ks[K];
    for (int i = 0; i < M; i++) {
      scanf("%d", &ks[i]);
    }

    static long long downdd[K], updd[K];
    long long sum = 0;
    for (int i = 0; i < M-2; i++) {
      sum += ks[i];
      downdd[i] = sum + b * ks[i+1];
    }
    sum = 0;
    for (int i = M-3; i >= 0; i--) {
      sum += ks[i+2];
      updd[i] = sum + a * ks[i+1];
    }

    static long long downd[K], upd[K];
    downd[0] = b * ks[0];
    for (int i = 1; i < M-1; i++) {
      downd[i] = downd[i-1] + downdd[i-1];
    }
    upd[M-2] = a * ks[M-1];
    for (int i = M-3; i >= 0; i--) {
      upd[i] = upd[i+1] + updd[i];
    }

    static long long down[K], up[K];
    down[0] = 0;
    for (int i = 1; i < M; i++) {
      down[i] = down[i-1] + downd[i-1];
    }
    up[M-1] = 0;
    for (int i = M-2; i >= 0; i--) {
      up[i] = up[i+1] + upd[i];
    }

    int ans = 0;
    long long m = down[0] + up[0];
    for (int i = 1; i < M; i++) {
      const long long x = down[i] + up[i];
      if (x < m) {
        m = x;
        ans = i;
      }
    }
    printf("%d\n", ans+1);
  }
  return 0;
}