#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool solve(const vector<pair<int,int> >& v, int D)
{
  const int N = v.size();
  vector<int> dist(N, 0);
  dist[0] = v[0].first;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      int d = v[j].first - v[i].first;
      if (d <= dist[i]) {
        dist[j] = max(dist[j], min(d, v[j].second));
      }
    }
  }
  for (int i = 0; i < N; i++) {
    if (v[i].first + dist[i] >= D) {
      return true;
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    vector<pair<int,int> > v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].first >> v[i].second;
    }
    int D;
    cin >> D;
    cout << "Case #" << Ti << ": " << (solve(v, D) ? "YES" : "NO") << endl;
  }
  return 0;
}
