#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int n, w;
  while (cin >> n >> w && n != 0) {
    vector<int> hist(100*n);
    for (int i = 0; i < n; i++) {
      int v;
      cin >> v;
      hist[v/w]++;
    }
    int leftist = 0;
    for (int i = 0; i < 100*n; i++) {
      if (hist[i] != 0) {
        leftist = i;
      }
    }
    const double m = *max_element(hist.begin(), hist.end());
    double ans = 0.01;
    for (int i = 0; i <= leftist; i++) {
      double color = double(leftist-i)/leftist;
      double prop = hist[i] / m;
      ans += color*prop;
    }
    printf("%.6f\n", ans);
  }
  return 0;
}
