#include <cstdio>
using namespace std;

int f(long long n, long long x, long long y)
{
  if (n == 1) {
    return 1;
  }
  const long long m = n>>1L;
  if (x < m) {
    if (y < m) {
      return f(m, x, y);
    } else {
      return f(m, x, y-m);
    }
  } else {
    if (y < m) {
      return f(m, x-m, y);
    } else {
      return -f(m, x-m, y-m);
    }
  }
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    long long n, x, y, w, h;
    scanf("%lld %lld %lld %lld %lld", &n, &x, &y, &w, &h);
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (j != 0) {
          putchar(' ');
        }
        printf("%d", f(n, y+i, x+j));
      }
      putchar('\n');
    }
    putchar('\n');
  }
}
