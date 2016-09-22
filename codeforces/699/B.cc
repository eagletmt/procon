#include <iostream>
#include <vector>
using namespace std;

void solve(int N, int M, const vector<string> &grid) {
  int total = 0;
  vector<int> rows(N, 0), cols(M, 0);
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      if (grid[i][j] == '*') {
        ++rows[i];
        ++cols[j];
        ++total;
      }
    }
  }

  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      int c = rows[i] + cols[j];
      if (grid[i][j] == '*') {
        --c;
      }
      if (c == total) {
        cout << "YES" << endl;
        cout << i + 1 << " " << j + 1 << endl;
        return;
      }
    }
  }

  cout << "NO" << endl;
}

int main() {
  int N, M;
  cin >> N >> M;
  vector<string> grid(N);
  for (int i = 0; i < N; i++) {
    cin >> grid[i];
  }

  solve(N, M, grid);

  return 0;
}
