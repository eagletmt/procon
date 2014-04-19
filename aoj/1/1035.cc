#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int W, Q;
  while (cin >> W >> Q && !(W == 0 && Q == 0)) {
    vector<pair<int,int> > cats(Q);
    vector<bool> used(W, false);
    for (int i = 0; i < Q; i++) {
      char sw;
      int id;
      cin >> sw >> id;
      if (sw == 's') {
        int w;
        cin >> w;

        int b = -1, c = 0;
        for (int j = 0; j < W; j++) {
          if (used[j]) {
            c = 0;
          } else {
            c++;
            if (c == w) {
              b = j - w + 1;
              break;
            }
          }
        }
        if (b == -1) {
          cout << "impossible" << endl;
        } else {
          for (int j = 0; j < w; j++) {
            used[b+j] = true;
          }
          cats[id] = make_pair(b, w);
          cout << b << endl;
        }
      } else {
        int b = cats[id].first;
        int w = cats[id].second;
        for (int j = 0; j < w; j++) {
          used[b+j] = false;
        }
      }
    }
    cout << "END" << endl;
  }
  return 0;
}
