#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(int X, vector<int>& files)
{
  int ans = 0;
  while (!files.empty()) {
    const int w1 = files.back();
    files.erase(files.begin() + files.size()-1);
    vector<int>::iterator it = files.begin();
    while (it != files.end()) {
      if (*it > X-w1) {
        break;
      }
      ++it;
    }
    if (it != files.begin()) {
      --it;
      files.erase(it);
    } else {
    }
    ++ans;
  }
  return ans;
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N, X;
    cin >> N >> X;
    vector<int> files(N);
    for (int i = 0; i < N; i++) {
      cin >> files[i];
    }

    sort(files.begin(), files.end());
    cout << solve(X, files) << endl;
  }
  return 0;
}
