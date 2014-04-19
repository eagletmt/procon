#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct cmp
{
  const vector<pair<int,int> >& v;
  cmp(const vector<pair<int,int> >& a) : v(a) {}
  bool operator()(int i, int j) const
  {
    return v[i].second > v[j].second;
  }
};

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, K;
    cin >> N >> K;
    vector<pair<int,int> > v(N);
    int left = 1000000, right = 0;
    for (int i = 0; i < N; i++) {
      int y;
      cin >> v[i].first >> y >> v[i].second >> y;
      if (v[i].first > v[i].second) {
        swap(v[i].first, v[i].second);
      }
      left = min(left, v[i].first);
      right = max(right, v[i].second);
    }

    vector<int> removed(N, false);
    for (int x = left; x <= right; x++) {
      vector<int> a;
      for (int i = 0; i < N; i++) {
        if (!removed[i] && v[i].first <= x && x <= v[i].second) {
          a.push_back(i);
        }
      }
      const int M = int(a.size()) - K;
      if (M > 0) {
        sort(a.begin(), a.end(), cmp(v));
        for (int i = 0; i < M; i++) {
          removed[a[i]] = true;
        }
      }
    }
    cout << count(removed.begin(), removed.end(), true) << endl;
  }
  return 0;
}