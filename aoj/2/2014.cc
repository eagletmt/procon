#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int w, h;
  while (cin >> w >> h && h != 0) {
    vector<vector<char> > grid(h, vector<char>(w));
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        cin >> grid[i][j];
      }
    }
    
    int white = 0, black = 0;
    for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
        if (grid[i][j] != '.') {
          continue;
        }
        int color = 0;  // uninitialized
        queue<pair<int,int> > q;
        q.push(make_pair(i, j));
        grid[i][j] = ' ';
        int count = 1;
        while (!q.empty()) {
          const pair<int,int> p = q.front();
          q.pop();
          const int a = p.first;
          const int b = p.second;
          for (int d = 0; d < 4; d++) {
            static const int dir_i[] = {1, -1, 0, 0};
            static const int dir_j[] = {0, 0, 1, -1};
            const int k = a + dir_i[d];
            const int l = b + dir_j[d];
            if (0 <= k && k < h && 0 <= l && l < w) {
              if (grid[k][l] == 'W') {
                if (color == 0 || color == 1) {
                  color = 1;
                } else {
                  color = -1;
                }
              } else if (grid[k][l] == 'B') {
                if (color == 0 || color == 2) {
                  color = 2;
                } else {
                  color = -1;
                }
              } else if (grid[k][l] == '.') {
                grid[k][l] = ' ';
                q.push(make_pair(k, l));
                count++;
              }
            }
          }
        }
        if (color == 1) {
          white += count;
        } else if (color == 2) {
          black += count;
        }
      }
    }
    cout << black << ' ' << white << endl;
  }
  return 0;
}
