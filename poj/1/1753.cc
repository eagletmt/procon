#include <iostream>
#include <vector>
#include <set>

using namespace std;
typedef unsigned board;

int flip(board b, int i, int j)
{
  b ^= 1 << 4*i + j;

  if (i != 0) {
    b ^= 1 << 4*(i-1) + j;
  }
  if (i != 3) {
    b ^= 1 << 4*(i+1) + j;
  }
  if (j != 0) {
    b ^= 1 << 4*i + j - 1;
  }
  if (j != 3) {
    b ^= 1 << 4*i + j + 1;
  }
  return b;
}

bool finish(board b)
{
  return b == 0 || b == 0xFFFF;
}

board encode(const vector<string>& v)
{
  board b = 0;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      if (v[i][j] == 'b') {
        b |= 1 << 4*i + j;
      }
    }
  }
  return b;
}

string decode(board b)
{
  string s;
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 4; j++) {
      s += (b & (1 << 4*i + j)) ? 'b' : 'w';
    }
    s += '\n';
  }
  return s;
}

int solve(board b)
{
  vector<board> cur(1);
  cur[0] = b;
  set<board> saw;
  int c = 0;

  while (!cur.empty()) {
    vector<board> next;
    c++;
    for (int i = 0; i < cur.size(); i++) {
      for (int j = 0; j < 4; j++) {
        for (int k = 0; k < 4; k++) {
          board t = cur[i];
          t = flip(t, j, k);

          if (finish(t)) {
            return c;
          }
          if (saw.find(t) == saw.end()) {
            saw.insert(t);
            next.push_back(t);
          }
        }
      }
    }
    cur.swap(next);
  }
  return -1;
}

int main(void)
{
  vector<string> v(4);
  cin >> v[0];
  cin >> v[1];
  cin >> v[2];
  cin >> v[3];
  /*
  v[0] = "bwwb";
  v[1] = "bbwb";
  v[2] = "bwwb";
  v[3] = "bwww";
  */

  board b = encode(v);
  if (finish(b)) {
    cout << 0 << endl;
  } else {
    int ans = solve(b);
    if (ans == -1) {
      cout << "Impossible" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}

