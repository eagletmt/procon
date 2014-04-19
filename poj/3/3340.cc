#include <iostream>
#include <string>
using namespace std;

int solve(const string& w, const string& x)
{
  if (w.find('?') == string::npos) {
    if (x < w) {
      return 1;
    } else {
      return 0;
    }
  }

  const int n = w.size();
  int ans = 0;
  for (int i = 0; i < n; i++) {
    if (w[i] == '?') {
      int s = 9-(x[i]-'0');
      for (int j = i+1; j < n; j++) {
        if (w[j] == '?') {
          s *= 10;
        }
      }
      ans += s;
    } else if (w[i] > x[i]) {
      int s = 1;
      for (int j = i+1; j < n; j++) {
        if (w[j] == '?') {
          s *= 10;
        }
      }
      ans += s;
      break;
    } else if (w[i] < x[i]) {
      break;
    }
  }
  return ans;
}

int main()
{
  string w;
  while (cin >> w && w != "#") {
    string x;
    cin >> x;
    cout << solve(w, x) << endl;
  }
  return 0;
}