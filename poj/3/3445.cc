#include <iostream>
#include <string>
using namespace std;

int decode(const string& str)
{
  int n = 0, d = 0;
  for (string::const_iterator it = str.begin(); it != str.end(); ++it) {
    if (*it == '{') {
      ++d;
    } else if (*it == '}') {
      --d;
      if (d == 1) {
        ++n;
      }
    }
  }
  return n;
}

string tbl[16];
void build()
{
  tbl[0] = "{}";
  for (int i = 1; i <= 15; i++) {
    tbl[i] = "{{}";
    for (int j = 1; j < i; j++) {
      tbl[i] += "," + tbl[j];
    }
    tbl[i] += "}";
  }
}

string encode(int n)
{
  return tbl[n];
}

int main()
{
  build();
  int T;
  cin >> T;
  while (T-- > 0) {
    string s, t;
    cin >> s >> t;
    cout << encode(decode(s) + decode(t)) << endl;
  }
  return 0;
}