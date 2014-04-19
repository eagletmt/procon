#include <cstdio>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

int main()
{
  for (int P; scanf("%d", &P) != EOF && P != 0;) {
    map<int, vector<int> > mx, my;
    for (int i = 0; i < P; i++) {
      int x, y;
      scanf("%d %d", &x, &y);
      mx[x].push_back(y);
      my[y].push_back(x);
    }
    long long ans = 0LL;
    for (map<int,vector<int> >::iterator it(mx.begin()); it != mx.end(); ++it) {
      assert(it->second.size() % 2 == 0);
      sort(it->second.begin(), it->second.end());
      for (vector<int>::const_iterator jt(it->second.begin()); jt != it->second.end(); jt += 2) {
        ans += static_cast<long long>(*(jt+1)) - *jt;
      }
    }
    for (map<int,vector<int> >::iterator it(my.begin()); it != my.end(); ++it) {
      assert(it->second.size() % 2 == 0);
      sort(it->second.begin(), it->second.end());
      for (vector<int>::const_iterator jt(it->second.begin()); jt != it->second.end(); jt += 2) {
        ans += static_cast<long long>(*(jt+1)) - *jt;
      }
    }
    printf("The length of the fence will be %lld units.\n", ans);
  }
  return 0;
}