#include <iostream>
#include <sstream>
#include <set>
using namespace std;

string inventory(const string& n)
{
  int digits[10] = {0};
  for (string::const_iterator it(n.begin()); it != n.end(); ++it) {
    digits[*it-'0']++;
  }

  ostringstream ss;
  for (int i = 0; i < 10; i++) {
    if (digits[i] != 0) {
      ss << digits[i] << i;
    }
  }
  return ss.str();
}

struct entry {
  string n;
  int i;
  entry(const string& n_, int i_) : n(n_), i(i_) {}
  bool operator<(const entry& a) const
  {
    return less<string>()(n, a.n);
  }
};

int main(void)
{
  static const int K = 15;
  string s;
  while (cin >> s && s != "-1") {
    set<entry> seen;
    seen.insert(entry(s, 0));

    cout << s << ' ';
    int i = 1;
    for (; i <= K; i++) {
      string t = inventory(s);
      if (t == s) {
        if (i == 1) {
          cout << "is self-inventorying" << endl;
        } else {
          cout << "is self-inventorying after " << i-1 << " steps" << endl;
        }
        break;
      } else {
        const pair<set<entry>::iterator, bool> r = seen.insert(entry(t, i));
        if (!r.second) {
          cout << "enters an inventory loop of length " << i - r.first->i << endl;
          break;
        }
      }
      s = t;
    }
    if (i == K+1) {
      string t = inventory(s);
      if (t == s) {
        cout << "is self-inventorying after " << i-1 << " steps" << endl;
      } else {
        cout << "can not be classified after " << K << " iterations" << endl;
      }
    }
  }
  return 0;
}
