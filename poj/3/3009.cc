#include <iostream>
#include <vector>
using namespace std;

int ans = 100;

void dfs(int i, int j, vector<vector<int> >& board, int depth)
{
  if (depth > 10 || depth >= ans) {
    return;
  }

  if (board[i][j] == 3) {
    ans = min(ans, depth);
    return;
  }

  const int H = board.size(), W = board[0].size();
  for (int d = 0; d < 4; d++) {
    static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
    int k = i, l = j;
    while (0 <= k && k < H && 0 <= l && l < W && board[k][l] == 0) {
      k += di[d];
      l += dj[d];
    }
    if (0 <= k && k < H && 0 <= l && l < W) {
      if (board[k][l] == 1) {
        if (i != k-di[d] || j != l-dj[d]) {
          board[k][l] = 0;
          dfs(k - di[d], l - dj[d], board, depth+1);
          board[k][l] = 1;
        }
      } else {
        dfs(k, l, board, depth+1);
      }
    }
  }
}

int main()
{
  int W, H;
  while (cin >> W >> H && W != 0) {
    vector<vector<int> > board(H, vector<int>(W));
    int k = -1, l = -1;
    for (int i = 0; i < H; i++) {
      for (int j = 0; j < W; j++) {
        cin >> board[i][j];
        if (board[i][j] == 2) {
          board[i][j] = 0;
          k = i;
          l = j;
        }
      }
    }
    ans = 100;
    dfs(k, l, board, 0);
    if (ans == 100) {
      cout << "-1" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}