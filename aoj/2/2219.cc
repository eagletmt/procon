#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

struct bydol
{
  int C;
  int vals[3];
};

int do_dp(const vector<bydol>& v, int M, int n)
{
  const int N = v.size();
  vector<int> dp(M+1, 0);
  int ans = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j+v[i].C <= M; j++) {
      dp[j+v[i].C] = max(dp[j+v[i].C], dp[j] + v[i].vals[n]);
      ans = max(ans, dp[j+v[i].C]);
    }
  }

  return ans;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    int N, M;
    {
      istringstream iss(line);
      iss >> N >> M;
    }
    vector<bydol> v(N);
    for (int i = 0; i < N; i++) {
      getline(cin, line); // ignore name
      getline(cin, line);
      {
        istringstream iss(line);
        iss >> v[i].C >> v[i].vals[0] >> v[i].vals[1] >> v[i].vals[2];
      }
    }

    int w = do_dp(v, M, 0);
    int d = do_dp(v, M, 1);
    int l = do_dp(v, M, 2);
    cout << max(w, max(d, l)) << endl;
  }
  return 0;
}
