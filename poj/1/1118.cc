#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<int> P;

inline int cross(const P& a, const P& b) { return a.real()*b.imag() - b.real()*a.imag(); }

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<P> v;
    for (int i = 0; i < N; i++) {
      int n, d;
      cin >> n >> d;
      v.push_back(P(n, d));
    }
    int ans = 0;
    for (int i = 0; i < N; i++) {
      for (int j = i+1; j < N; j++) {
        int c = 2;
        const P p = v[j] - v[i];
        for (int k = j+1; k < N; k++) {
          const P q = v[k] - v[i];
          if (cross(p, q) == 0) {
            ++c;
          }
        }
        ans = max(ans, c);
      }
    }
    cout << ans << endl;
  }
  return 0;
}
