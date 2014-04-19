#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int A, N;
    cin >> A >> N;
    vector<int> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }
    sort(v.begin(), v.end());

    int ans = N;
    int c = 0;
    int i = 0;
    while (i < N && c < ans) {
      if (v[i] < A) {
        A += v[i];
        ++i;
      } else {
        ans = min(ans, c + N - i);
        A += A-1;
        c++;
      }
    }
    ans = min(ans, c);
    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
