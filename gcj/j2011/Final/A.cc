#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
  static const double PI = acos(-1.0);
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int K;
    cin >> K;
    vector<int> es(K);
    for (int i = 0; i < K; i++) {
      cin >> es[i];
    }

    sort(es.rbegin(), es.rend());
    vector<int>::const_iterator it = es.begin();
    int e1 = *it++;
    int e2 = *it++;
    double ans = e1*e2;
    for (; it != es.end(); ++it) {
      ans += e1 * *it;
      e1 = e2;
      e2 = *it;
    }
    ans += e1 * e2;
    printf("Case #%d: %.9f\n", Ti, ans * sin(2*PI/K) / 2.0);
  }
  return 0;
}
