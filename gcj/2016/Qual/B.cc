#include <iostream>
#include <vector>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    string line;
    cin >> line;
    vector<int> pancakes;
    for (char c : line) {
      pancakes.push_back(c == '+' ? 0 : 1);
    }
    const int N = pancakes.size();

    int ans = 0;
    int flip = 0;
    for (int i = N-1; i >= 0; i--) {
      if ((pancakes[i] ^ flip) == 1) {
        ++ans;
        flip ^= 1;
      }
    }
    cout << "Case #" << Ti << ": " << ans << endl;
  }
  return 0;
}
