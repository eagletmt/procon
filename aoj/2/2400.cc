#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct team
{
  int id;
  int ac;
  int penalty;
  vector<int> wa;
  team(int i, int P) : id(i), ac(0), penalty(0), wa(P, 0) {}

  bool operator<(const team& t) const
  {
    if (ac != t.ac) {
      return ac > t.ac;
    } else if (penalty != t.penalty) {
      return penalty < t.penalty;
    } else {
      return id < t.id;
    }
  }
};

int main()
{
  int T, P, R;
  while (cin >> T >> P >> R && T != 0) {
    vector<team> v;
    for (int i = 0; i < T; i++) {
      v.push_back(team(i+1, P));
    }
    for (int i = 0; i < R; i++) {
      int tid, pid, tm;
      string s;
      cin >> tid >> pid >> tm >> s;
      --tid;  --pid;
      team& t = v[tid];
      if (t.wa[pid] == -1) {
        continue;
      }
      if (s == "CORRECT") {
        ++t.ac;
        t.penalty += 1200*t.wa[pid] + tm;
      } else {
        ++t.wa[pid];
      }
    }
    sort(v.begin(), v.end());
    for (vector<team>::const_iterator it = v.begin(); it != v.end(); ++it) {
      cout << it->id << ' ' << it->ac << ' ' << it->penalty << endl;
    }
  }
  return 0;
}
