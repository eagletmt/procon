#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int solve(const vector<string>& v)
{
  const int N = v.size();
  vector<unsigned> indices(N, 0);

  int ans = 0;

  while (indices[0] < v[0].size()) {
    const char c = v[0][indices[0]];
    vector<int> lens(N, 0);
    int maxlen = 0, minlen = 10000000;
    for (int i = 0; i < N; i++) {
      while (indices[i] < v[i].size() && v[i][indices[i]] == c) {
        ++indices[i];
        ++lens[i];
      }
      if (lens[i] == 0) {
        throw "Fegla Won";
      }
      maxlen = max(maxlen, lens[i]);
      minlen = min(minlen, lens[i]);
    }

    int best = 10000000;
    for (int l = minlen; l <= maxlen; l++) {
      int d = 0;
      for (int i = 0; i < N; i++) {
        d += abs(lens[i] - l);
      }
      best = min(best, d);
    }
    ans += best;
  }

  for (int i = 0; i < N; i++) {
    if (indices[i] != v[i].size()) {
      throw "Fegla Won";
    }
  }

  return ans;
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N;
    cin >> N;
    vector<string> v(N);
    for (int i = 0; i < N; i++) {
      cin >> v[i];
    }

    try {
      cout << solve(v) << endl;
    } catch (const char *msg) {
      cout << msg << endl;
    }
  }
  return 0;
}
