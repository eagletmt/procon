#include <cstdio>
#include <vector>
using namespace std;

bool ok(const vector<int>& a, int k, int t)
{
  int r = 0;
  for (vector<int>::const_iterator it(a.begin()); it != a.end(); ++it) {
    if (*it > t) {
      const int d = *it - t;
      r += d/(k-1);
      if (d % (k-1) != 0) {
        ++r;
      }
      if (r > t) {
        return false;
      }
    }
  }
  return true;
}

int main()
{
  int n;
  while (scanf("%d", &n) == 1) {
    vector<int> a(n);
    int left = 0, right = 0;
    for (int i = 0; i < n; i++) {
      scanf("%d", &a[i]);
      right = max(right, a[i]);
    }
    int k;
    scanf("%d", &k);

    if (k != 1) {
      // binary search
      while (left < right) {
        const int mid = (right + left)/2;
        if (ok(a, k, mid)) {
          right = mid;
        } else {
          left = mid+1;
        }
      }
    }
    printf("%d\n", right);
  }
  return 0;
}