#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct record
{
  int time, pc, student;
  bool login;
  record(int t, int n, int m, int s)
    : time(t), pc(n), student(m), login(s != 0)
  {}
};

struct analyzer
{
  vector<record> rs;
  int query(int start, int end, int student) const
  {
    static const int N = 1261;
    int acc[N];
    fill_n(acc, N, 0);
    for (vector<record>::const_iterator it(rs.begin()); it != rs.end(); ++it) {
      if (it->student == student) {
        if (it->login) {
          ++acc[it->time];
        } else {
          --acc[it->time];
        }
      }
    }
    for (int i = 1; i < N; i++) {
      acc[i] += acc[i-1];
    }
    int ans = 0;
    for (int t = start; t < end; t++) {
      if (acc[t] > 0) {
        ++ans;
      }
    }
    return ans;
  }
};

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    analyzer a;
    int r;
    cin >> r;
    for (int i = 0; i < r; i++) {
      int t, n, m, s;
      cin >> t >> n >> m >> s;
      a.rs.push_back(record(t, n, m, s));
    }
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
      int s, e, m;
      cin >> s >> e >> m;
      cout << a.query(s, e, m) << endl;
    }
  }
  return 0;
}