#include <cstdio>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  while (scanf("%d", &N) == 1 && N != 0) {
    unsigned long long a[10000];
    for (int i = 0; i < N; i++) {
      int c[5];
      for (int j = 0; j < 5; j++) {
        scanf("%d", &c[j]);
      }
      sort(c, c+5);
      unsigned long long s = 0;
      for (int j = 0; j < 5; j++) {
        s = (s << 9) | static_cast<unsigned long long>(c[j]);
      }
      a[i] = s;
    }
    sort(a, a+N);

    int c = 0, ans = 0;
    unsigned long long p = static_cast<unsigned long long>(-1);
    int s = 0;
    for (int i = 0; i < N; i++) {
      if (p == a[i]) {
        ++s;
      } else {
        if (c < s) {
          c = s;
          ans = c;
        } else if (c == s) {
          ans += c;
        }
        s = 1;
      }
      p = a[i];
    }
    if (c < s) {
      ans = c;
    } else if (c == s) {
      ans += c;
    }
    printf("%d\n", ans);
  }
  return 0;
}