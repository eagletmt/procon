#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct board
{
  vector<string> grid;
  int dir;
  int i, j;
  board() : grid(8) {}
  void move(int n)
  {
    if (dir == 0) {
      // up
      const int next_i = max(i - n, 0);
      queue<char> q;
      for (int k = i-1; k >= next_i; k--) {
        if (grid[k][j] != '.') {
          q.push(grid[k][j]);
          grid[k][j] = '.';
        }
      }
      for (int k = next_i-1; k >= 0 && !q.empty(); k--) {
        const char c = grid[k][j];
        grid[k][j] = q.front();
        q.pop();
        if (c != '.') {
          q.push(c);
        }
      }
      i = next_i;
    } else if (dir == 2) {
      // down
      const int next_i = min(i + n, 7);
      queue<char> q;
      for (int k = i+1; k <= next_i; k++) {
        if (grid[k][j] != '.') {
          q.push(grid[k][j]);
          grid[k][j] = '.';
        }
      }
      for (int k = next_i+1; k < 8 && !q.empty(); k++) {
        const char c = grid[k][j];
        grid[k][j] = q.front();
        q.pop();
        if (c != '.') {
          q.push(c);
        }
      }
      i = next_i;
    } else if (dir == 1) {
      // right
      const int next_j = min(j + n, 7);
      queue<char> q;
      for (int l = j+1; l <= next_j; l++) {
        if (grid[i][l] != '.') {
          q.push(grid[i][l]);
          grid[i][l] = '.';
        }
      }
      for (int l = next_j+1; l < 8 && !q.empty(); l++) {
        const char c = grid[i][l];
        grid[i][l] = q.front();
        q.pop();
        if (c != '.') {
          q.push(c);
        }
      }
      j = next_j;
    } else {
      // left
      const int next_j = max(j - n, 0);
      queue<char> q;
      for (int l = j-1; l >= next_j; l--) {
        if (grid[i][l] != '.') {
          q.push(grid[i][l]);
          grid[i][l] = '.';
        }
      }
      for (int l = next_j-1; l >= 0 && !q.empty(); l--) {
        const char c = grid[i][l];
        grid[i][l] = q.front();
        q.pop();
        if (c != '.') {
          q.push(c);
        }
      }
      j = next_j;
    }
  }

  void right() { dir = (dir+1) % 4; }
  void left() { dir = (dir+3) % 4; }
  void print() const
  {
    for (int k = 0; k < 8; k++) {
      for (int l = 0; l < 8; l++) {
        if (k == i && l == j) {
          static const char t[] = "^>v<";
          cout << t[dir];
        } else {
          cout << grid[k][l];
        }
      }
      cout << endl;
    }
  }
};

int main()
{
  string s;
  while (cin >> s && s != "--") {
    board b;
    b.grid[0] = s;
    for (int i = 1; i < 8; i++) {
      cin >> b.grid[i];
      for (int j = 0; j < 8; j++) {
        static const string v = "^>v<";
        const int n = v.find(b.grid[i][j]);
        if (n != string::npos) {
          b.i = i;
          b.j = j;
          b.dir = n;
          b.grid[i][j] = '.';
        }
      }
    }

    while (cin >> s && s != "#") {
      if (s == "move") {
        int n;
        cin >> n;
        b.move(n);
      } else {
        string dir;
        cin >> dir;
        if (dir == "left") {
          b.left();
        } else if (dir == "right") {
          b.right();
        } else if (dir == "back") {
          b.left();
          b.left();
        }
      }
    }
    b.print();
    cout << endl;
  }
  return 0;
}