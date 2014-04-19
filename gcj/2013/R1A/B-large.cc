#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int f(int E, int R, const vector<int>& v, const vector<int>& x, int idx)
{
  const int N = v.size();
  int e1 = E;
  for (int i = 0; i < idx; i++) {
    e1 = min(E, e1 - x[i] + R);
  }
  int e2 = 0;
  for (int i = N-1; i > idx; i--) {
    e2 = max(0, e2 - R + x[i]);
  }
  return e1 - e2;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int E, R, N;
    cin >> E >> R >> N;
    vector<int> v(N);
    vector<pair<int,int> > w(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
      w[i] = make_pair(v[i], i);
    }
    sort(w.rbegin(), w.rend());

    vector<int> x(N, 0);
    long long ans = 0;
    for (int i = 0; i < N; i++) {
      const int idx = w[i].second;
      const long long y = f(E, R, v, x, idx);
      ans += y * v[idx];
      x[idx] = y;
    }

    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
