#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

struct rect
{
  double x1, y1, x2, y2;
};

struct event
{
  int idx;
  double x;
  event(int i, double x_) : idx(i), x(x_) {}

  bool operator<(const event& that) const { return x < that.x; }
};

double total_height(const vector<rect>& rs, const vector<bool>& present)
{
  const int N = rs.size();
  vector<event> evts;
  for (int i = 0; i < N; i++) {
    if (present[i]) {
      evts.push_back(event(i, rs[i].y1));
      evts.push_back(event(i, rs[i].y2));
    }
  }
  sort(evts.begin(), evts.end());
  vector<bool> fs(N, false);
  double bot = 0.0;
  int n = 0;
  double h = 0.0;
  for (vector<event>::const_iterator it = evts.begin(); it != evts.end(); ++it) {
    if (!fs[it->idx]) {
      // start
      if (n == 0) {
        bot = it->x;
      }
      ++n;
    } else {
      // end
      --n;
      if (n == 0) {
        h += it->x - bot;
      }
    }
    fs[it->idx] = !fs[it->idx];
  }
  return h;
}

int main()
{
  int Ti = 0;
  int N;
  while (scanf("%d", &N) != EOF && N != 0) {
    vector<rect> rs(N);
    vector<event> evts;
    for (int i = 0; i < N; i++) {
      scanf("%lf %lf %lf %lf", &rs[i].x1, &rs[i].y1, &rs[i].x2, &rs[i].y2);
      evts.push_back(event(i, rs[i].x1));
      evts.push_back(event(i, rs[i].x2));
    }
    sort(evts.begin(), evts.end());

    vector<bool> present(N, false);
    vector<event>::const_iterator it = evts.begin();
    const vector<event>::const_iterator last = evts.end();
    present[it->idx] = true;
    double ans = 0.0;
    for (++it; it != last; ++it) {
      const double h = total_height(rs, present);
      ans += h * (it->x - (it-1)->x);
      present[it->idx] = !present[it->idx];
    }
    printf("Test case #%d\n", ++Ti);
    printf("Total explored area: %.2f\n\n", ans);
  }
  return 0;
}