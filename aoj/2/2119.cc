#include <iostream>
#include <vector>
using namespace std;

int solve(int N, int M)
{
  vector<int> group(M+1, 0);
  group[0] = N;
  int ans = 0;
  for (; group[M] == 0; ++ans) {
    vector<int> next(M+1, 0);
    for (int i = 0; i <= M; i++) {
      const int x = group[i] / 2;
      next[i+1] += x;
      next[0] += x;
      next[i] += group[i] - 2*x;
    }
    group.swap(next);
  }
  return ans;
}

int main()
{
  int T = 0;
  int N, M;
  while (cin >> N >> M && N != 0) {
    cout << "Case " << ++T << ": " << solve(N, M) << endl;
  }
  return 0;
}
