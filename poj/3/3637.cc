#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int t;
  cin >> t;
  while (t-- > 0) {
    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      cin >> v[i];
    }
    sort(v.begin(), v.end(), greater<int>());
    int ans = 0;
    for (int i = 2; i < v.size(); i += 3) {
      ans += v[i];
    }
    cout << ans << endl;
  }
  return 0;
}
