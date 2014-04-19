#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int M, C, W;
    cin >> M >> C >> W;
    vector<pair<int,int> > ab(C);
    for (int i = 0; i < C; i++) {
      cin >> ab[i].first >> ab[i].second;
    }
    int ans = W;
    for (vector<pair<int,int> >::const_reverse_iterator it = ab.rbegin(); it != ab.rend(); ++it) {
      if (ans <= it->second) {
        ans += it->first-1;
      } else if (ans < it->first + it->second) {
        ans -= it->second;
      }
    }
    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
