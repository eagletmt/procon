#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M;
  cin >> N >> M;
  vector<int> xs, ys;
  vector<pair<int,int> > v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i].first >> v[i].second;
    xs.push_back(v[i].first);
    ys.push_back(v[i].second);
  }
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.end());
  sort(ys.begin(), ys.end());
  ys.erase(unique(ys.begin(), ys.end()), ys.end());

  static const int MAXN = 5000;
  static int grid[MAXN][MAXN];
  for (vector<pair<int,int> >::const_iterator it = v.begin(); it != v.end(); ++it) {
    const int xi = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), it->first));
    const int yi = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), it->second));
    ++grid[xi][yi];
  }
  static int sums[MAXN+1][MAXN+1];
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      sums[i+1][j+1] = sums[i][j+1] + sums[i+1][j] - sums[i][j] + grid[i][j];
    }
  }

  for (int i = 0; i < M; i++) {
    int x1, y1, x2, y2;
    cin >> x1 >> y1 >> x2 >> y2;
    const int xi1 = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), x1));
    const int yi1 = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y1));
    const int xi2 = distance(xs.begin(), lower_bound(xs.begin(), xs.end(), x2+1));
    const int yi2 = distance(ys.begin(), lower_bound(ys.begin(), ys.end(), y2+1));
    cout << sums[xi2][yi2] - sums[xi2][yi1] - sums[xi1][yi2] + sums[xi1][yi1] << endl;
  }
  return 0;
}
