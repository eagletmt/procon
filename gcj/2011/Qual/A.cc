#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; ++Ti) {
    int N;
    cin >> N;
    vector<pair<char,int> > seq(N);
    int next_orange = -1, next_blue = -1;
    for (int i = 0; i < N; i++) {
      cin >> seq[i].first >> seq[i].second;
      if (next_orange == -1 && seq[i].first == 'O') {
        next_orange = seq[i].second;
      } else if (next_blue == -1 && seq[i].first == 'B') {
        next_blue = seq[i].second;
      }
    }

    int orange = 1, blue = 1;
    int step = 0;
    for (int i = 0; i < N; i++) {
      if (seq[i].first == 'O') {
        const int s = abs(next_orange - orange)+1;
        step += s;
        if (blue < next_blue) {
          blue += min(s, abs(next_blue - blue));
        } else if (blue > next_blue) {
          blue -= min(s, abs(next_blue - blue));
        }
        orange = next_orange;
        for (int j = i+1; j < N; j++) {
          if (seq[j].first == 'O') {
            next_orange = seq[j].second;
            break;
          }
        }
      } else {
        const int s = abs(next_blue - blue)+1;
        step += s;
        if (orange < next_orange) {
          orange += min(s, abs(next_orange - orange));
        } else if (orange > next_orange) {
          orange -= min(s, abs(next_orange - orange));
        }
        blue = next_blue;
        for (int j = i+1; j < N; j++) {
          if (seq[j].first == 'B') {
            next_blue = seq[j].second;
            break;
          }
        }
      }
    }

    cout << "Case #" << Ti << ": " << step << endl;
  }
  return 0;
}
