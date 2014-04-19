#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

bool do_combine(const map<string,char>& m, char c, string& ans)
{
  if (ans.empty()) {
    return false;
  }
  const string k = ans.substr(ans.size()-1) + c;
  const map<string,char>::const_iterator it = m.find(k);
  if (it != m.end()) {
    ans[ans.size()-1] = it->second;
    return true;
  } else {
    return false;
  }
}

bool do_oppose(const set<string>& s, char c, string& ans)
{
  for (int i = ans.size()-1; i >= 0; i--) {
    const string k = ans.substr(i, 1) + c;
    if (s.count(k)) {
      ans.clear();
      return true;
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; ++Ti) {
    int C;
    cin >> C;
    map<string,char> combine;
    for (int i = 0; i < C; i++) {
      string s;
      cin >> s;
      combine.insert(make_pair(s.substr(0, 2), s[2]));
      swap(s[0], s[1]);
      combine.insert(make_pair(s.substr(0, 2), s[2]));
    }
    int D;
    cin >> D;
    set<string> oppose;
    for (int i = 0; i < D; i++) {
      string s;
      cin >> s;
      oppose.insert(s);
      swap(s[0], s[1]);
      oppose.insert(s);
    }
    int N;
    cin >> N;
    string elts;
    cin >> elts;
    string ans = string(1, elts[0]);
    for (int i = 1; i < N; i++) {
      const char c = elts[i];
      if (!do_combine(combine, c, ans) && !do_oppose(oppose, c, ans)) {
        ans += c;
      }
    }

    cout << "Case #" << Ti << ": [";
    for (string::const_iterator it(ans.begin()); it != ans.end(); ++it) {
      if (it != ans.begin()) {
        cout << ", ";
      }
      cout << *it;
    }
    cout << "]" << endl;
  }
  return 0;
}
