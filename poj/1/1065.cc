#include <cstdio>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static pair<int,int> a[5000];
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &a[i].first, &a[i].second);
    }
    sort(a, a+N, greater<pair<int,int> >());

    // LIS
    vector<int> v;
    for (int i = 0; i < N; i++) {
      const int x = a[i].second;
      vector<int>::iterator it = lower_bound(v.begin(), v.end(), x);
      if (it == v.end()) {
        v.push_back(x);
      } else {
        *it = x;
      }
    }
    printf("%lu\n", v.size());
  }
  return 0;
}