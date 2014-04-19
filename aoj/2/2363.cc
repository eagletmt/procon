#include <cstdio>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;
static const double EPS = 1e-7;

int main()
{
  int T;
  scanf("%d", &T);
  double maxE = 0.0;
  while (T-- > 0) {
    int N, M;
    scanf("%d %d", &N, &M);
    vector<double> vs(M), rs(M);
    double R = 0.0;
    for (int i = 0; i < M; i++) {
      scanf("%lf %lf", &vs[i], &rs[i]);
      R += rs[i];
    }
    maxE = max(maxE, inner_product(vs.begin(), vs.end(), rs.begin(), 0.0) / R);
  }

  int P, Q;
  scanf("%d %d", &P, &Q);
  vector<double> vs(Q), rs(Q);
  double R = 0.0;
  for (int i = 0; i < Q; i++) {
    scanf("%lf %lf", &vs[i], &rs[i]);
    R += rs[i];
  }

  const double E = inner_product(vs.begin(), vs.end(), rs.begin(), 0.0) / R;
  if (maxE - E > EPS) {
    puts("YES");
  } else {
    puts("NO");
  }
  return 0;
}
