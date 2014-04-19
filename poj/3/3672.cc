#include <cstdio>
using namespace std;

int main()
{
  int m,t,u,f,d;
  scanf("%d%d%d%d%d", &m, &t, &u, &f, &d);
  getchar();

  char ch;
  int ans = 0;
  for (int i = 0; i < t; i++) {
    scanf("%c", &ch);
    getchar();
    switch (ch) {
      case 'f':
        m -= f*2;
        break;
      case 'u':
      case 'd':
        m -= u+d;
        break;
    }
    if (m >= 0) {
      ++ans;
    }
  }
  printf("%d", ans);

  return 0;
}
