#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int A, B;
    scanf("%d %d", &A, &B);
    int ans = 0;
    for (int n = A; n < B; n++) {
      int e = 1, d = 0;
      while (e <= n) {
        e = 10*e;
        ++d;
      }
      e /= 10;
      --d;
      int m = n;
      int v[10];
      int *p = v;
      while (d-- > 0) {
        m = m%e*10 + m/e;
        if (n < m && m <= B) {
          *p = m;
          ++p;
        }
      }
      sort(v, p);
      ans += unique(v, p) - v;
    }
    printf("Case #%d: %d\n", Ti, ans);
  }
  return 0;
}
