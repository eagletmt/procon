#include <cstdio>
#include <vector>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &v[i]);
    }

    int ans = 1;
    int acc = 1;
    for (int i = 1; i < N; i++) {
      if (acc % 2 == 0) {
        if (v[i-1] < v[i]) {
          ++acc;
        }
      } else {
        if (v[i-1] > v[i]) {
          ++acc;
        }
      }
      ans = max(ans, acc);
    }
    printf("%d\n", ans);
  }
  return 0;
}
