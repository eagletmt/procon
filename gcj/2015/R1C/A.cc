#include <iostream>
using namespace std;

int solve2(int C, int W)
{
  const int x = (C - W) / W;
  return x + min(C - x*W, W+1);
}

int solve(int R, int C, int W)
{
  return (C / W) * (R - 1) + solve2(C, W);
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int R, C, W;
    cin >> R >> C >> W;
    cout << "Case #" << Ti << ": " << solve(R, C, W) << endl;
  }
  return 0;
}
