#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(vector<int>& A)
{
  int ans = 0;
  while (!A.empty()) {
    vector<int>::iterator it = min_element(A.begin(), A.end());
    const int n = distance(A.begin(), it);
    ans += min(n, int(A.size())-n-1);
    A.erase(it);
  }
  return ans;
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
      cin >> A[i];
    }
    cout << solve(A) << endl;
  }
  return 0;
}
