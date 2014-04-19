#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int S, T, M;
  int t = 1;
  while (cin >> S >> T >> M && !(S == 0 && T == 0 && M == 0)) {
    vector<bool> cond_b(S), cond_c(S);
    for (int i = 0; i < S; i++) {
      int s, b, c;
      cin >> s >> b >> c;
      cond_b[s-1] = b == 1;
      cond_c[s-1] = c == 1;
    }
    vector<bool> cond_a(S);
    for (int i = 0; i < T; i++) {
      int s, c;
      cin >> s >> c;
      cond_a[s-1] = cond_a[s-1] || c >= M;
    }

    int c = 0;
    for (int i = 0; i < S; i++) {
      c += cond_a[i] + cond_b[i] + cond_c[i];
    }
    cout << "Case " << t << ": " << c << endl;
    t++;
  }
  return 0;
}
