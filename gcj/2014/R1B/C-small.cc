#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

bool ok(const vector<vector<int> >& g, const vector<int>& a)
{
  const int N = a.size();

  stack<int> s;
  s.push(a[0]);
  for (int i = 1; i < N && !s.empty(); ) {
    const int cur = s.top();
    const int next = a[i];
    if (g[cur][next]) {
      s.push(next);
      ++i;
    } else {
      s.pop();
    }
  }
  return !s.empty();
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N, M;
    cin >> N >> M;
    vector<string> codes(N);
    for (int i = 0; i < N; i++) {
      cin >> codes[i];
    }
    vector<vector<int> > g(N, vector<int>(N, false));
    for (int i = 0; i < M; i++) {
      int from, to;
      cin >> from >> to;
      --from; --to;
      g[from][to] = g[to][from] = true;
    }

    vector<int> a(N);
    for (int i = 0; i < N; i++) {
      a[i] = i;
    }

    string ans;
    do {
      if (ok(g, a)) {
        string code;
        for (int i = 0; i < N; i++) {
          code += codes[a[i]];
        }
        if (ans.empty() || code < ans) {
          ans = code;
        }
      }
    } while (next_permutation(a.begin(), a.end()));

    cout << ans << endl;
  }
  return 0;
}
