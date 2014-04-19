#include <iostream>
#include <cstdio>
#include <cmath>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
static const double EPS = 1e-6;

bool possible(double t, int D, const vector<int>& ps)
{
  vector<int>::const_iterator it = ps.begin();
  double p = *it - t;
  for (++it; it != ps.end(); ++it) {
    if (p+D < *it) {
      // back
      p = max(p+D, *it - t);
    } else {
      if (*it + t >= p+D) {
        // ok
        p += D;
      } else {
        return false;
      }
    }
  }
  return true;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; ++Ti) {
    cout << "Case #" << Ti << ": ";

    int D, C;
    cin >> C >> D;
    vector<int> ps;
    for (int i = 0; i < C; i++) {
      int P, V;
      cin >> P >> V;
      for (int j = 0; j < V; j++) {
        ps.push_back(P);
      }
    }

    double left = 0.0, right = D*ps.size();
    for (int i = 0; i < 200; i++) {
      const double mid = (left + right) / 2.0;
      if (possible(mid, D, ps)) {
        right = mid;
      } else {
        left = mid;
      }
    }

    printf("%0.6f\n", left);
  }
  return 0;
}
