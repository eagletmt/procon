#include <iostream>
#include <algorithm>
using namespace std;

int solve(int N, const int *a, const int *b)
{
  static int v[1000];
  fill_n(v, N, 0);
  int c = 0;
  for (int got = 0; got < 2*N; c++) {
    int idx = -1;
    for (int i = 0; i < N; i++) {
      if (v[i] < 2 && b[i] <= got) {
        // get 2-star
        got += 2 - v[i];
        v[i] = 2;
        goto NEXT;
      } else if (v[i] == 0 && a[i] <= got) {
        if (idx == -1 || b[i] > b[idx]) {
          idx = i;
        }
      }
    }
    if (idx == -1) {
      return -1;
    }
    got += 1;
    v[idx] = 1;
NEXT:
    ;
  }
  return c;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    static int a[1000], b[1000];
    for (int i = 0; i < N; i++) {
      cin >> a[i] >> b[i];
    }
    const int ans = solve(N, a, b);
    cout << "Case #" << Ti << ": ";
    if (ans == -1) {
      cout << "Too Bad" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
