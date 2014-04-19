#include <iostream>
#include <set>
#include <algorithm>
#include <iterator>
using namespace std;

int main()
{
  int N, W;
  cin >> N >> W;

  set<int> s;
  int count = 0;
  while (N--) {
    int x, y;
    cin >> x >> y;
    if (y == 0) {
      s.clear();
    } else {
      set<int>::const_iterator it = s.find(y);
      if (it == s.end()) {
        count++;
        it = s.insert(y).first;
      }
      s.erase(++it, s.end());
    }
  }
  cout << count << endl;
  return 0;
}
