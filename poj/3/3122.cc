#include <iostream>
#include <cstdio>
#include <vector>
#include <numeric>
#include <cmath>
using namespace std;
static const double PI = atan2(0.0, -0.0);

int count(const vector<int>& pies, double size)
{
  int c = 0;
  for (vector<int>::const_iterator it(pies.begin()); it != pies.end(); ++it) {
    const double s = PI * *it * *it;
    c += static_cast<int>(s / size);
  }
  return c;
}

double solve(const vector<int>& pies, int F)
{
  double low = 0.0, high = 0.0;
  for (vector<int>::const_iterator it(pies.begin()); it != pies.end(); ++it) {
    high += PI * *it * *it;
  }
  high /= F;

  for (int i = 0; i < 150; i++) {
    const double mid = (low + high) / 2.0;
    if (count(pies, mid) > F) {
      low = mid;
    } else {
      high = mid;
    }
  }
  return high;
}

int main()
{
  int T;
  cin >> T;
  while (T-- > 0) {
    int N, F;
    cin >> N >> F;
    vector<int> pies; pies.reserve(N);
    for (int i = 0; i < N; i++) {
      int r;
      cin >> r;
      pies.push_back(r);
    }
    printf("%.4f\n", solve(pies, F));
  }
  return 0;
}
