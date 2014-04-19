#include <iostream>
#include <vector>
#include <limits>
using namespace std;

int main(void)
{
  int N, P;
  cin >> N >> P;
  vector<int> simplests(P, 0), hardests(P, 0);
  for (int t = 0; t < N; t++) {
    vector<int> rates(P, 0);
    int low = numeric_limits<int>::max();
    int high = numeric_limits<int>::min();
    for (int i = 0; i < P; i++) {
      cin >> rates[i];
      low = min(low, rates[i]);
      high = max(high, rates[i]);
    }
    for (int i = 0; i < P; i++) {
      if (low == rates[i]) {
        simplests[i]++;
      }
      if (high == rates[i]) {
        hardests[i]++;
      }
    }
  }

  vector<int> ans;
  for (int i = 0; i < P; i++) {
    if (simplests[i] > N/2 && hardests[i] == 0) {
      ans.push_back(i+1);
    }
  }
  if (ans.empty()) {
    cout << 0 << endl;
  } else {
    cout << ans[0];
    for (vector<int>::const_iterator it(ans.begin()+1); it != ans.end(); ++it) {
      cout << ' ' << *it;
    }
    cout << endl;
  }
  return 0;
}
