#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int simulate(const vector<pair<int,int> >& stones, int D)
{
  pair<int,int> bunkers[2] = {make_pair(0, 0), make_pair(0, 0)};
  int i = 0;
  for (vector<pair<int,int> >::const_iterator it(stones.begin()); it != stones.end(); ++it) {
    bunkers[i].first += it->first;
    bunkers[i].second += it->second;
    if (bunkers[i].first - bunkers[1-i].first > D) {
      i = 1-i;
    }
  }
  return bunkers[1].second;
}

int main()
{
  int N, D;
  cin >> N >> D;
  vector<pair<int,int> > stones(N);
  for (int i = 0; i < N; i++) {
    cin >> stones[i].first >> stones[i].second;
  }
  sort(stones.begin(), stones.end());
  int ans = 0;
  do {
    ans = max(ans, simulate(stones, D));
  } while (next_permutation(stones.begin(), stones.end()));
  cout << ans << endl;
  return 0;
}