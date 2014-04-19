#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
typedef unsigned long long ull;

int main()
{
  static const ull M = 1000000000000000000ULL;
  vector<ull> v;
  for (ull a = 1ULL; a < M; a *= 2ULL) {
    for (ull b = 1ULL; a*b < M; b *= 3ULL) {
      for (ull c = 1ULL; a*b*c < M; c *= 5ULL) {
        for (ull d = 1ULL; a*b*c*d < M; d *= 7ULL) {
          v.push_back(a*b*c*d);
        }
      }
    }
  }
  sort(v.begin(), v.end());

  int T;
  cin >> T;
  while (T-- > 0) {
    int x;
    cin >> x;
    cout << v[x-1] << endl;
  }
  return 0;
}