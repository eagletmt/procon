#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct cmp {
  bool operator()(const pair<double,string>& lhs, const pair<double,string>& rhs) const
  {
    return lhs.first == rhs.first ? lhs.second < rhs.second : lhs.first > rhs.first;
  }
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<pair<double,string> > v(N);
    for (int i = 0; i < N; i++) {
      string L;
      int P, A, B, C, D, E, F, S, M;
      cin >> L >> P >> A >> B >> C >> D >> E >> F >> S >> M;
      int t = A + B + C + (D + E)*M;
      int c = F * S * M;
      double e = double(c - P) / t;
      v[i] = make_pair(e, L);
    }
    sort(v.begin(), v.end(), cmp());
    for (int i = 0; i < N; i++) {
      cout << v[i].second << endl;
    }
    cout << '#' << endl;
  }
  return 0;
}
