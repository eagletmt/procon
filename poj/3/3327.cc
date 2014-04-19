#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct cake
{
  int w, d;
  int born;
  cake() {}
  cake(int a, int b, int c) : w(a), d(b), born(c) {}
  int area() const { return w*d; }
  bool operator<(const cake& that) const
  {
    if (born == that.born) {
      return area() < that.area();
    } else {
      return born < that.born;
    }
  }
};

struct by_area
{
  bool operator()(const cake& lhs, const cake& rhs) const
  {
    return lhs.area() < rhs.area();
  }
};

int main()
{
  int N, W, D;
  while (cin >> N >> W >> D && W != 0) {
    vector<cake> cakes; cakes.reserve(N);
    cakes.push_back(cake(W, D, 0));
    for (int i = 0; i < N; i++) {
      int p, s;
      cin >> p >> s;
      --p;
      cake& c = cakes[p];
      s %= 2*(c.w + c.d);
      c.born = i;
      cake c2(c);
      if (0 < s && s < c.w) {
        c2.w = c.w - s;
        c.w = s;
      } else if (c.w < s && s < c.w+c.d) {
        c2.d = c.d - (s - c.w);
        c.d = s - c.w;
      } else if (c.w+c.d < s && s < 2*c.w+c.d) {
        c2.w = c.w - (s - c.w - c.d);
        c.w = s - c.w - c.d;
      } else {
        c2.d = c.d - (s - 2*c.w - c.d);
        c.d = s - 2*c.w - c.d;
      }
      cakes.push_back(c2);
      sort(cakes.begin(), cakes.end());
    }
    sort(cakes.begin(), cakes.end(), by_area());
    for (vector<cake>::const_iterator it(cakes.begin()); it != cakes.end(); ++it) {
      if (it != cakes.begin()) {
        cout << ' ';
      }
      cout << it->area();
    }
    cout << endl;
  }
  return 0;
}