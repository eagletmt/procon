#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N;
    cin >> N;
    vector<pair<int,int> > ropes(N);
    for (int i = 0; i < N; i++) {
      cin >> ropes[i].first >> ropes[i].second;
    }
    sort(ropes.begin(), ropes.end());
    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        if (ropes[i].second > ropes[j].second) {
          ans++;
        }
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}

