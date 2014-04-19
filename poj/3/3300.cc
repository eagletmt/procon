#include <iostream>
#include <cstdio>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct ratio {
  int n, d;
  ratio(int a, int b) : n(a), d(b) {}
  bool operator<(const ratio& r) const
  {
    return n*r.d > d*r.n;
  }
};

int main()
{
  int F, R;
  while (cin >> F && F != 0) {
    cin >> R;
    vector<int> fs(F);
    for (int i = 0; i < F; i++) {
      cin >> fs[i];
    }
    vector<int> rs(R);
    for (int i = 0; i < R; i++) {
      cin >> rs[i];
    }

    vector<ratio> vs;
    for (int i = 0; i < F; i++) {
      for (int j = 0; j < R; j++) {
        vs.push_back(ratio(fs[i], rs[j]));
      }
    }
    sort(vs.begin(), vs.end());
    vector<double> spreads;
    for (int i = 0; i < vs.size()-1; i++) {
      spreads.push_back(((double)vs[i].n*vs[i+1].d)/((double)vs[i].d*vs[i+1].n));
    }
    const double ans = *max_element(spreads.begin(), spreads.end());
    printf("%.2f\n", ans);
  }
  return 0;
}