#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>
using namespace std;

string merge(const vector<string>& v)
{
  string ans = "";
  for (int i = 0; i < v.size(); i++) {
    const string& s = v[i];
    for (int j = 0; j < ans.size(); j++) {
      int k = 0;
      for (; k < s.size() && j+k < ans.size(); k++) {
        if (ans[j+k] != s[k]) {
          break;
        }
      }
      if (j+k == ans.size()) {
        ans += s.substr(k);
        goto NEXT;
      }
    }
    ans += s;
NEXT:
    ;
  }
  return ans;
}

int main()
{
  int N;
  cin >> N;
  vector<string> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i];
  }
  sort(v.begin(), v.end());
  int ans = numeric_limits<int>::max();
  do {
    ans = min(ans, int(merge(v).size()));
  } while (next_permutation(v.begin(), v.end()));
  cout << ans << endl;
  return 0;
}
