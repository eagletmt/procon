#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, L;
  cin >> N >> L;
  vector<int> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());

  int ans = 0;
  for (int left = 0, right = N-1, done = 0; done < N; ++ans) {
    if (left < right && v[left] + v[right] > L) {
      ++done;
      --right;
    } else {
      done += 2;
      --right;
      ++left;
    }
  }
  cout << ans << endl;
  return 0;
}