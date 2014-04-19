#include <iostream>
#include <vector>
#include <deque>
#include <sstream>
#include <algorithm>
using namespace std;

struct player
{
  int number;
  string name;
  char role;
  int record;
};

struct team
{
  vector<player> gk, df, mf, st;
  int ndf, nmf, nst;
};

struct captain
{
  bool operator()(const player& lhs, const player& rhs) const
  {
    if (lhs.record != rhs.record) {
      return lhs.record < rhs.record;
    } else {
      return lhs.number < rhs.number;
    }
  }
};

struct by_number
{
  bool operator()(const player& lhs, const player& rhs) const
  {
    return lhs.number < rhs.number;
  }
};

deque<player> solve(team& t)
{
  deque<player> ans;
  if (t.gk.empty() || t.mf.size() < t.nmf || t.df.size() < t.ndf || t.st.size() < t.nst) {
    return ans;
  }

  const by_number c = by_number();
  player& gk = *min_element(t.gk.begin(), t.gk.end(), c);
  ans.push_back(gk);
  sort(t.df.begin(), t.df.end(), c);
  copy(t.df.begin(), t.df.begin()+t.ndf, back_inserter(ans));
  sort(t.mf.begin(), t.mf.end(), c);
  copy(t.mf.begin(), t.mf.begin()+t.nmf, back_inserter(ans));
  sort(t.st.begin(), t.st.end(), c);
  copy(t.st.begin(), t.st.begin()+t.nst, back_inserter(ans));

  deque<player>::iterator it = max_element(ans.begin(), ans.end(), captain());
  const player cap = *it;
  ans.erase(it);
  ans.push_front(cap);
  return ans;
}

int main()
{
  string line;
  while (getline(cin, line) && line != "0") {
    team t;
    do {
      istringstream iss(line);
      player p;
      iss >> p.number >> p.name >> p.role;
      p.record = 0;
      int y0, y1;
      char c;
      while (iss >> y0 >> c >> y1) {
        p.record += y1 - y0 + 1;
      }
      switch (p.role) {
        case 'G': t.gk.push_back(p);  break;
        case 'D': t.df.push_back(p);  break;
        case 'M': t.mf.push_back(p);  break;
        case 'S': t.st.push_back(p);  break;
      }
    } while (getline(cin, line) && line.size() > 5);

    t.ndf = line[0]-'0';
    t.nmf = line[2]-'0';
    t.nst = line[4]-'0';
    const deque<player> ans = solve(t);
    if (ans.empty()) {
      cout << "IMPOSSIBLE TO ARRANGE" << endl;
    } else {
      for (deque<player>::const_iterator it(ans.begin()); it != ans.end(); ++it) {
        cout << it->number << ' ' << it->name << ' ' << it->role << endl;
      }
    }
    cout << endl;
  }
  return 0;
}