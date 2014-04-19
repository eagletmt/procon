#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct cmp
{
  bool operator()(const pair<int,int>& a, const pair<int,int>& b) const
  {
    if (a.first == b.first) {
      return a.second < b.second;
    } else {
      return a.first > b.first;
    }
  }
};

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    static pair<int,int> a[20000];
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &a[i].first, &a[i].second);
    }
    sort(a, a+N, cmp());

    // LIS
    vector<int> v;
    for (int i = 0; i < N; i++) {
      const int x = a[i].second;
      vector<int>::iterator it = upper_bound(v.begin(), v.end(), x);
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
