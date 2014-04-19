#include <iostream>
#include <sstream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

bool valid(int i, int j)
{
  return 0 <= i && i < 8 && 0 <= j && j < 8;
}

int main()
{
  string line;
  while (cin >> line) {
    vector<string> grid(1, line);
    for (int i = 1; i < 8; i++) {
      cin >> line;
      grid.push_back(line);
    }
    cin >> line;
    const char me = line[0];
    const char opp = me == 'X' ? 'O' : 'X';

    vector<string> output;
    for (int i = 0; i < 8; i++) {
      for (int j = 0; j < 8; j++) {
        if (grid[i][j] != me) {
          continue;
        }

        for (int d = 0; d < 8; d++) {
          static const int di[] = {-1, -1, -1, 0, 0, 1, 1, 1};
          static const int dj[] = {-1, 0, 1, -1, 1, -1, 0, 1};
          int cnt = 0;
          for (int k = i, l = j; valid(k, l); k += di[d], l += dj[d]) {
            if (grid[k][l] != '.') {
              ++cnt;
            }
          }
          for (int k = i, l = j; valid(k, l); k -= di[d], l -= dj[d]) {
            if (grid[k][l] != '.') {
              ++cnt;
            }
          }
          --cnt;

          const int k = i + cnt*di[d];
          const int l = j + cnt*dj[d];
          if (valid(k, l)) {
            ostringstream oss;
            if (grid[k][l] == me) {
              goto FAIL1;
            }
            for (int a = i, b = j; a != k || b != l; a += di[d], b += dj[d]) {
              if (grid[a][b] == opp) {
                goto FAIL1;
              }
            }
            oss << char('A'+i) << j+1 << '-' << char('A'+k) << l+1;
            output.push_back(oss.str());
FAIL1:
            ;
          }
        }
      }
    }
    if (output.empty()) {
      cout << "No moves are possible" << endl;
    } else {
      sort(output.begin(), output.end());
      copy(output.begin(), output.end(), ostream_iterator<string>(cout, "\n"));
    }
    cout << endl;
  }
  return 0;
}