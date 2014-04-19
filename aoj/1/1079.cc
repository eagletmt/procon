#include <cstdio>
#include <algorithm>
using namespace std;
struct order { int a, b, o; };

int main()
{
  int R, C, Q;
  while (scanf("%d %d %d", &R, &C, &Q) != EOF && R != 0) {
    static const int K = 50000;
    static bool doner[K], donec[K];
    fill_n(doner, R, false);
    fill_n(donec, C, false);
    static order os[K];
    for (int i = 0; i < Q; i++) {
      scanf("%d %d %d", &os[i].a, &os[i].b, &os[i].o);
    }

    long long row = R, col = C;
    long long ans = 0LL;
    for (int i = Q-1; i >= 0; i--) {
      if (os[i].a) {
        // column
        if (!donec[os[i].b]) {
          donec[os[i].b] = true;
          --col;
          if (os[i].o) {
            ans += row;
          }
        }
      } else {
        // row
        if (!doner[os[i].b]) {
          doner[os[i].b] = true;
          --row;
          if (os[i].o) {
            ans += col;
          }
        }
      }
    }
    printf("%lld\n", ans);
  }
  return 0;
}
