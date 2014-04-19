#include <iostream>
#include <vector>
using namespace std;

int main()
{
  string cmd;
  while (cin >> cmd && cmd != "ENDOFINPUT") {
    int R, C;
    cin >> R >> C;
    vector<vector<int> > orig(R, vector<int>(C));
    for (int i = 0; i < R; i++) {
      string line;
      cin >> line;
      for (int j = 0; j < C; j++) {
        orig[i][j] = line[j] - '0';
      }
    }
    cin >> cmd;

    for (int i = 0; i < R-1; i++) {
      for (int j = 0; j < C-1; j++) {
        cout << (orig[i][j] + orig[i][j+1] + orig[i+1][j] + orig[i+1][j+1]) / 4;
      }
      cout << endl;
    }
  }
  return 0;
}