#include <iostream>
#include <set>
using namespace std;

bool ok(const string& s)
{
  const int N = s.size();
  for (int d = 1; d < N; d++) {
    set<string> t;
    for (int i = 0; i+d < N; i++) {
      string x;
      x += s[i];
      x += s[i+d];
      if (!t.insert(x).second) {
        //cerr << "eq at i=" << i << " " << s[i] << " and " << s[i+d] << ", d = " << d << endl;
        return false;
      }
    }
  }
  return true;
}

int main()
{
  string s;
  while (getline(cin, s) && s != "*") {
    if (ok(s)) {
      cout << s << " is surprising." << endl;
    } else {
      cout << s << " is NOT surprising." << endl;
    }
  }
  return 0;
}
