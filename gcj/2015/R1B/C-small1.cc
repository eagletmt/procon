#include <iostream>
#include <vector>
using namespace std;

struct hiker
{
  int D, H, M;
};

vector<hiker> flatten(const vector<hiker>& v)
{
  vector<hiker> w;
  const int N = v.size();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < v[i].H; j++) {
      hiker h;
      h.D = v[i].D;
      h.H = 1;
      h.M = v[i].M + i;
      w.push_back(h);
    }
  }
  return w;
}

bool ok(hiker h1, hiker h2)
{
  double t1 = h1.M * (360.0 - h1.D)/360.0;
  double t2 = h2.M * (360.0 - h2.D)/360.0;
  if (t1 > t2) {
    swap(h1, h2);
    swap(t1, t2);
  }
  return (t2 - t1) < h1.M;
}

int solve(const vector<hiker>& v)
{
  if (v.size() == 1) {
    return 0;
  }
  if (v.size() > 2) {
    throw __LINE__;
  }
  const hiker h1 = v[0], h2 = v[1];
  if (ok(h1, h2)) {
    return 0;
  } else {
    return 1;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    vector<hiker> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i].D >> v[i].H >> v[i].M;
    }
    cout << "Case #" << Ti << ": " << solve(flatten(v)) << endl;
  }
  return 0;
}
