#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int R, N;
  while (cin >> R >> N && N != -1) {
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }
    sort(v.begin(), v.end());

    int ans = 0;
    vector<int>::iterator it = v.begin();
    while (it != v.end()) {
      const int back = *it;
      for (; it != v.end() && (*it - back) <= R; ++it);
      --it;
      ++ans;
      const int mid = *it;
      for (; it != v.end() && (*it - mid) <= R; ++it);
    }
    cout << ans << endl;
  }
  return 0;
}