#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    vector<int> ps(N);
    for (int i = 0; i < N; i++) {
      cin >> ps[i];
    }

    vector<int> v(1, 0);
    for (int i = 0; i < N; i++) {
      v.push_back(ps[i]);
      for (int j = i; j < N; j++) {
        if (ps[i] + ps[j] <= M) {
          v.push_back(ps[i] + ps[j]);
        }
      }
    }
    sort(v.begin(), v.end());

    int ans = 0;
    for (vector<int>::const_iterator it(v.begin()); it != v.end(); ++it) {
      vector<int>::const_iterator jt = lower_bound(v.begin(), v.end(), M - *it);
      if (jt != v.begin()) {
        --jt;
        ans = max(ans, *it + *jt);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
