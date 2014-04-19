#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }

    int ans = 0;
    for (int i = N-1; i >= 0; i--) {
      for (int j = 0; j < i; j++) {
        if (v[j] > v[j+1]) {
          ++ans;
          swap(v[j], v[j+1]);
        }
      }
    }
    cout << "Scenario #" << Ti << ":" << endl;
    cout << ans << endl << endl;
  }
  return 0;
}