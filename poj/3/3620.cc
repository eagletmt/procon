#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int N, M, K;
  cin >> N >> M >> K;

  vector<vector<bool> > grid(N, vector<bool>(M, false));
  for (int i = 0; i < K; i++) {
    int row, col;
    cin >> row >> col;
    grid[row-1][col-1] = true;
  }

  static const int dir_row[] = {-1, 0, 0, 1};
  static const int dir_col[] = {0, -1, 1, 0};
  int max_size = 1;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (!grid[i][j]) {
        continue;
      }

      vector<int> cur(1, i*M + j);
      grid[i][j] = false;
      int size = 1;
      while (!cur.empty()) {
        vector<int> next;
        for (vector<int>::const_iterator it(cur.begin()); it != cur.end(); ++it) {
          for (int d = 0;  d < 4; d++) {
            const int row = *it / M + dir_row[d];
            const int col = *it % M + dir_col[d];
            if (row >= 0 && col >= 0 && row < N && col < M && grid[row][col]) {
              next.push_back(row*M + col);
              grid[row][col] = false;
              size++;
            }
          }
        }
        cur = next;
      }
      max_size = max(max_size, size);
    }
  }
  cout << max_size << endl;
  return 0;
}
