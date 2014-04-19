#include <cstdio>
using namespace std;

int comb[27][27];

double solve(int N, int c, int X, int Y)
{
  if (Y - X <= 2*(c-1) && X + Y <= 2*(c-1)) {
    // inside the triangle
    return 1.0;
  }
  if (Y - X == 2*c || X + Y == 2*c) {
  } else {
    // outside the triangle
    return 0.0;
  }

  const int rest = N - (2*c*c - c);
  const int upto = 2*c;
  int total = 0, cnt = 0;
  for (int s = 0; s < (1<<rest); s++) {
    int l = 0, r = 0;
    bool ok = false;
    int a = 1;
    for (int i = 0; i < rest; i++) {
      if (l == upto || r == upto) {
        ++a;
      }
      if (s & (1<<i)) {
        // left
        ++l;
        if (l > upto) {
          goto invalid;
        }
      } else {
        // right
        ++r;
        if (r > upto) {
          goto invalid;
        }
      }
      if ((X < 0 && Y == l-1) || (X > 0 && Y == r-1)) {
        ok = true;
      }
    }
    total += a;
    if (ok) {
      cnt += a;
    }
    continue;
invalid:
    ;
  }
  return double(cnt)/double(total);
}

int main()
{
  for (int i = 0; i <= 26; i++) {
    comb[i][0] = 1;
    comb[i][i] = 1;
  }
  for (int n = 1; n <= 26; n++) {
    for (int k = 1; k < n; k++) {
      comb[n][k] = comb[n-1][k] + comb[n-1][k-1];
    }
  }

  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, X, Y;
    scanf("%d %d %d", &N, &X, &Y);

    int c = 1;
    for (int n = 1; n <= N; c++) {
      n += 4*c + 1;
    }
    --c;
    printf("Case #%d: %.7f\n", Ti, solve(N, c, X, Y));
  }
  return 0;
}
