#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    unsigned A, B, K;
    cin >> A >> B >> K;

    int ans = 0;
    for (unsigned i = 0; i < A; i++) {
      for (unsigned j = 0; j < B; j++) {
        if ((i & j) < K) {
          ++ans;
        }
      }
    }

    cout << ans << endl;
  }
  return 0;
}
