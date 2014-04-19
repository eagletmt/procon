#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

bool win(const string& s, char c)
{
  for (int i = 0; i < 4; i++) {
    if (s[i] != 'T' && s[i] != c) {
      return false;
    }
  }
  return true;
}

char solve(const vector<string>& grid)
{
  string diag1, diag2;
  int ndots = 0;
  for (int i = 0; i < 4; i++) {
    if (win(grid[i], 'X')) {
      return 'X';
    } else if (win(grid[i], 'O')) {
      return 'O';
    }

    string col;
    for (int j = 0; j < 4; j++) {
      col += grid[j][i];
    }
    if (win(col, 'X')) {
      return 'X';
    } else if (win(col, 'O')) {
      return 'O';
    }

    diag1 += grid[i][i];
    diag2 += grid[i][3-i];
    ndots += count(grid[i].begin(), grid[i].end(), '.');
  }
  if (win(diag1, 'X') || win(diag2, 'X')) {
    return 'X';
  } else if (win(diag1, 'O') || win(diag2, 'O')) {
    return 'O';
  } else if (ndots == 0) {
    return '.';
  } else {
    return 0;
  }
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    vector<string> grid(4);
    for (int i = 0; i < 4; i++) {
      cin >> grid[i];
    }

    const char r = solve(grid);
    cout << "Case #" << Ti << ": ";
    if (r) {
      if (r == '.') {
        cout << "Draw" << endl;
      } else {
        cout << r << " won" << endl;
      }
    } else {
      cout << "Game has not completed" << endl;
    }
  }
  return 0;
}
