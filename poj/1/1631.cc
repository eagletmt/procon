#include <cstdio>
#include <vector>
#include <limits>
#include <algorithm>
using namespace std;

int lis(const vector<int>& v)
{
  const int N = v.size();
  vector<int> a(N, numeric_limits<int>::max());
  vector<int> id(N);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    id[i] = distance(a.begin(), lower_bound(a.begin(), a.end(), v[i]));
    a[id[i]] = v[i];
    ans = max(ans, id[i]+1);
  }
  return ans;
}

int main()
{
  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int P;
    scanf("%d", &P);
    vector<int> v(P);
    for (int i = 0; i < P; i++) {
      scanf("%d", &v[i]);
    }
    printf("%d\n", lis(v));
  }
  return 0;
}