#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int T;
  scanf("%d", &T);
  for (int Ti = 1; Ti <= T; Ti++) {
    int N, W, L;
    scanf("%d %d %d", &N, &W, &L);
    vector<pair<int,int> > r(N);
    for (int i = 0; i < N; i++) {
      scanf("%d", &r[i].first);
      r[i].second = i;
    }
    sort(r.rbegin(), r.rend());

    vector<pair<int,int> > ans(N);
    ans[r[0].second] = make_pair(0, 0);
    int x = r[0].first, y = 0;
    int ymax = r[0].first;
    for (int i = 1; i < N; i++) {
      int rr = r[i].first;
      int idx = r[i].second;
      if (x + rr <= W) {
        x += rr;
        ans[idx] = make_pair(x, y);
        x += rr;
        ymax = max(ymax, rr);
      } else {
        y += 2*ymax;
        x = 0;
        ans[idx] = make_pair(x, y);
        x += rr;
        ymax = rr;
      }
    }
    printf("Case #%d:", Ti);
    for (int i = 0; i < N; i++) {
      if (ans[i].second > L || ans[i].first > W) {
        throw "err";
      }
      printf(" %d %d", ans[i].first, ans[i].second);
    }
    putchar('\n');
  }
  return 0;
}
