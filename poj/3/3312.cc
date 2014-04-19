#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>
using namespace std;

bool check(vector<int>::const_iterator it, int k)
{
  const double sum = accumulate(it, it+k, 0);
  const double ave = sum / static_cast<double>(k);
  for (int i = 0; i < k; ++i, ++it) {
    if (abs(ave - *it) > 2) {
      return false;
    }
  }
  return true;
}

bool solve(const vector<int>& names, int k)
{
  for (vector<int>::const_iterator it(names.begin()); it != names.end(); it += k) {
    if (!check(it, k)) {
      return false;
    }
  }
  return true;
}

int main()
{
  int T = 0;
  int n, k;
  while (cin >> n >> k && n != 0) {
    vector<int> names(n);
    for (vector<int>::iterator it(names.begin()); it != names.end(); ++it) {
      string s;
      cin >> s;
      *it = s.size();
    }
    sort(names.begin(), names.end());
    cout << "Case " << ++T << ": " << (solve(names, k) ? "yes" : "no") << "\n" << endl;
  }
  return 0;
}