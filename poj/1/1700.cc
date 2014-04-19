#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N;
    cin >> N;
    vector<int> v(N);
    for (vector<int>::iterator it(v.begin()); it != v.end(); ++it) {
      cin >> *it;
    }
    sort(v.begin(), v.end());

    int s = 0;
    int i = N-1;
    for (i = N-1; i > 2; i -= 2) {
      s += min(v[i]+v[0]+v[i-1]+v[0], v[1]+v[0]+v[i]+v[1]);
    }
    if (i == 2) {
      s += v[2]+v[0]+v[1];
    } else {
      s += v[i];
    }
    cout << s << endl;
  }
  return 0;
}