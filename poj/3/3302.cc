#include <iostream>
#include <string>
using namespace std;

bool solve(const string& s1, const string& s2)
{
  string::size_type i = 0, j = 0;
  while (i < s1.size() && j < s2.size()) {
    if (s1[i] == s2[j]) {
      i++;
      j++;
    } else {
      i++;
    }
  }
  return j == s2.size();
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    string s1, s2;
    cin >> s1 >> s2;
    const string s3(s2.rbegin(), s2.rend());
    bool ans = solve(s1, s2) || solve(s1, s3);
    cout << (ans ? "YES" : "NO") << endl;
  }
  return 0;
}