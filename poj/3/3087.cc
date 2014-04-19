#include <iostream>
#include <set>
using namespace std;

string merge(const string& s1, const string& s2)
{
  string s12;
  for (string::size_type i = 0; i < s1.size(); i++) {
    s12 += s2[i];
    s12 += s1[i];
  }
  return s12;
}

int main()
{
  int N;
  cin >> N;
  for (int n = 1; n <= N; n++) {
    int C;
    cin >> C;
    string s1, s2, t;
    cin >> s1 >> s2 >> t;
    string s12 = merge(s1, s2);
    set<string> s;
    for (int c = 1; s.insert(s12).second; c++) {
      if (s12 == t) {
        cout << n << ' ' << c << endl;
        goto NEXT;
      }
      s1.assign(s12, 0, C);
      s2.assign(s12, C, 2*C);
      s12 = merge(s1, s2);
    }
    cout << n << " -1" << endl;
NEXT:
    ;
  }
  return 0;
}