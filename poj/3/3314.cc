#include <iostream>
#include <vector>
#include <queue>
#include <deque>

using namespace std;

int main()
{
  int n, w, b;
  while (cin >> n >> w >> b && n != 0) {
    vector<deque<string> > blocks;
    deque<string> block;
    for (int i = 0; i < n; i++) {
      int h;
      cin >> h;
      vector<string> plaque(h);
      for (int j = 0; j < h; j++) {
        cin >> plaque[j];
      }

      int j = 0;
      for (; j < block.size() && j < plaque.size(); j++) {
        for (int l = 0; l <= j; l++) {
          for (int k = 0; k < w; k++) {
            if (block[l][k] == 'X' && plaque[plaque.size()-l-1][k] == 'X') {
              goto L;
            }
          }
        }
      }
L:
      if (block.size() + plaque.size() - j > b) {
        //overed
        blocks.push_back(block);
        block.clear();
        for (int k = 0; k < plaque.size(); k++) {
          block.push_front(plaque[plaque.size()-k-1]);
        }
      } else {
        // merge
        for (int k = 0; k < j; k++) {
          for (int l = 0; l < w; l++) {
            if (block[k][l] == '.') {
              block[k][l] = plaque[plaque.size()-j+k][l];
            }
          }
        }
        for (int k = j; k < plaque.size(); k++) {
          block.push_front(plaque[plaque.size()-k-1]);
        }
      }
    }
    blocks.push_back(block);
    for (int i = 0; i < blocks.size(); i++) {
      if (i != 0) {
        cout << ' ';
      }
      cout << blocks[i].size();
      //for (int i = 0; i < block.size(); i++) { cout << block[i] << endl; }
    }
    cout << endl;
  }
  return 0;
}