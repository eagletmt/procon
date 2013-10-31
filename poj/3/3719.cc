#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
using namespace std;

struct node
{
  int left, right;
};

static const int MAXM = 16;
vector<unsigned> bit_patterns[MAXM+1];
node tree[100];
int M;
int weights[MAXM];

double dp[100][1<<MAXM];
int dp_w[100][1<<MAXM];

double calc(int lw, int rw)
{
  return fabs(0.5 - double(rw)/(lw + rw));
}

int solve(int n)
{
  if (tree[n].left < 0) {
    // leaf
    //printf("[%d] is leaf\n", n);
    for (int i = 0; i < M; i++) {
      dp[n][1<<i] = 0;
      dp_w[n][1<<i] = weights[i];
    }
    return 1;
  } else {
    const int left = tree[n].left;
    const int right = tree[n].right;
    const int lc = solve(left);
    const int rc = solve(right);
    const int c = lc + rc;
    //printf("[%d] has %d bits\n", n, c);
    for (vector<unsigned>::const_iterator it = bit_patterns[c].begin(); it != bit_patterns[c].end() && *it < (1U<<M); ++it) {
      const unsigned s = *it;
      //printf("  [%d] choose %u\n", n, s);
      for (int i = 1; i < c; i++) {
        //printf("    [%d] divide %d and %d\n", n, i, c-i);
        for (vector<unsigned>::const_iterator jt = bit_patterns[i].begin(); jt != bit_patterns[i].end(); ++jt) {
          const unsigned t = *jt;
          if ((s & t) != t) {
            continue;
          }
          const unsigned u = (s ^ t) & s;
          //printf("      [%d] choose %u and %u\n", n, t, u);
          const int lw = dp_w[left][t];
          const int rw = dp_w[right][u];
          //printf("      [%d] dp %g and %g\n", n, dp[left][t], dp[right][u]);
          //printf("      [%d] dp_w %d and %d\n", n, lw, rw);
          const double d = dp[left][t] + dp[right][u] + calc(lw, rw);
          //printf("      [%d] d %g\n", n, d);
          if (d < dp[n][s]) {
            dp[n][s] = d;
            dp_w[n][s] = lw + rw;
          }
        }
      }
    }
    return c;
  }
}

int main()
{
  for (unsigned s = 1; s < (1<<MAXM); s++) {
    bit_patterns[__builtin_popcount(s)].push_back(s);
  }

  int T;
  scanf("%d", &T);
  while (T-- > 0) {
    int N;
    scanf("%d", &N);
    for (int i = 0; i < N; i++) {
      scanf("%d %d", &tree[i].left, &tree[i].right);
      --tree[i].left;
      --tree[i].right;
    }
    scanf("%d", &M);
    for (int i = 0; i < M; i++) {
      scanf("%d", &weights[i]);
    }

    for (int i = 0; i < N; i++) {
      fill_n(dp[i], 1<<M, 1e10);
    }
    solve(0);
    printf("%.3f\n", dp[0][(1<<M)-1] * 1000);
  }
  return 0;
}
