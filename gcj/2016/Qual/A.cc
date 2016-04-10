#include <iostream>
#include <set>
using namespace std;

int main() {
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    cout << "Case #" << Ti << ": ";
    if (N == 0) {
      cout << "INSOMNIA" << endl;
      continue;
    }

    set<int> s;
    int n = 0;
    while (s.size() < 10) {
      n += N;
      for (int t = n; t > 0; t /= 10) {
        s.insert(t % 10);
      }
    }
    cout << n << endl;
  }
  return 0;
}
