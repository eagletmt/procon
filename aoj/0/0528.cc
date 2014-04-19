#include <iostream>
#include <vector>
using namespace std;

int solve(const string& s1, const string& s2)
{
  int max_idx1 = 0;
  int max_idx2 = 0;
  int max_len = 0;
  for (int i = -int(s1.size()); i <= int(s2.size()); i++) {
    int len = 0;
    for (int j = max(i, 0); j < int(min(s1.size()+i, s2.size())); j++) {
      if (s1[j-i] == s2[j]) {
        len++;
        if (len > max_len) {
          max_idx1 = j-i-len+1;
          max_idx2 = j-len+1;
          max_len = len;
        }
      } else {
        len = 0;
      }

    }
  }
  return max_len;
}

int main()
{
  string s1, s2;
  while (cin >> s1 >> s2) {
    cout << solve(s1, s2) << endl;
  }
  return 0;
}
