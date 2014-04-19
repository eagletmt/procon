#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

string suffix(int n)
{
  if ((n/10) % 10 == 1) {
    return "th";
  } else {
    switch (n % 10) {
      case 1: return "st";  break;
      case 2: return "nd";  break;
      case 3: return "rd";  break;
      default: return "th";
    }
  }
}

vector<int> build_table(int n)
{
  vector<int> tbl(n);
  tbl[0] = 1;
  vector<int> indexes(4, 0);
  for (int i = 1; i < n; i++) {
    static const int a[] = {2, 3, 5, 7};
    vector<pair<int,int> > v(4);
    for (int j = 0; j < 4; j++) {
      v[j] = make_pair(tbl[indexes[j]]*a[j], j);
    }
    sort(v.begin(), v.end());
    tbl[i] = v.front().first;
    for (vector<pair<int,int> >::const_iterator it = v.begin(); it != v.end() && it->first == v.front().first; ++it) {
      ++indexes[it->second];
    }
  }
  return tbl;
}

int main()
{
  const vector<int> v = build_table(5842);
  int n;
  while (cin >> n && n != 0) {
    cout << "The " << n << suffix(n) << " humble number is " << v[n-1] << "." << endl;
  }
  return 0;
}