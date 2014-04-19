#include <iostream>
#include <vector>
using namespace std;

bool check(const vector<vector<char> >& grid, char c, int K)
{
  const int N = grid.size();
  for (int i = 0; i < N; i++) {
    for (int j = 0; j <= N-K; j++) {
      int k;
      for (k = 0; k < K && grid[i][j+k] == c; k++);
      if (k == K) {
        return true;
      }
    }
  }
  for (int i = 0; i <= N-K; i++) {
    for (int j = 0; j < N; j++) {
      int k;
      for (k = 0; k < K && grid[i+k][j] == c; k++);
      if (k == K) {
        return true;
      }
    }
  }

  for (int i = 0; i <= N-K; i++) {
    for (int j = 0; j <= N-K; j++) {
      int k = 0;
      for (k = 0; k < K && grid[i+k][j+k] == c; k++);
      if (k == K) {
        return true;
      }
    }
  }
  for (int i = 0; i <= N-K; i++) {
    for (int j = K-1; j < N; j++) {
      int k = 0;
      for (k = 0; k < K && grid[i+k][j-k] == c; k++);
      if (k == K) {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, K;
    cin >> N >> K;
    vector<vector<char> > grid(N, vector<char>(N));
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      for (int j = 0; j < N; j++) {
        grid[j][N-1-i] = s[j];
      }
    }

    for (int i = N-2; i >= 0; i--) {
      for (int j = 0; j < N; j++) {
        if (grid[i+1][j] == '.') {
          for (int k = i+1; k < N && grid[k][j] == '.'; k++) {
            grid[k][j] = grid[k-1][j];
            grid[k-1][j] = '.';
          }
        }
      }
    }

    bool b = check(grid, 'B', K);
    bool r = check(grid, 'R', K);
    cout << "Case #" << t << ": ";
    if (b && r) {
      cout << "Both" <<endl;
    } else if (b) {
      cout << "Blue" << endl;
    } else if (r) {
      cout << "Red" << endl;
    } else {
      cout << "Neither" << endl;
    }

  }
  return 0;
}
