#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  static const int fact[] = {1, 1, 2, 6, 24, 120, 720, 5040, 40320, 362880};

  int n;
  while (scanf("%d", &n) == 1 && n >= 0) {
    if (n == 0) {
      puts("NO");
    } else {
      for (int i = 10; i >= 0; i--) {
        if (fact[i] <= n) {
          n -= fact[i];
        }
      }
      puts(n == 0 ? "YES" : "NO");
    }
  }
  return 0;
}