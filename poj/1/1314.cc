#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <complex>
using namespace std;
typedef complex<int> P;

bool rectp(P *ps)
{
  return
    ps[0].imag() == ps[1].imag()
    && ps[0].real() < ps[1].real()
    && ps[1].real() == ps[2].real()
    && ps[1].imag() > ps[2].imag()
    && ps[2].imag() == ps[3].imag()
    && ps[2].real() > ps[3].real()
    && ps[3].real() == ps[0].real()
    && ps[3].imag() < ps[0].imag();
}

int main()
{
  int N;
  for (int Ti = 1; cin >> N && N != 0; Ti++) {
    vector<char> cs(N);
    vector<P> ps(N);
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
      cin >> cs[i] >> ps[i].real() >> ps[i].imag();
      a[i] = i;
    }

    cout << "Point set " << Ti << ":";
    if (N < 4) {
      cout << " No rectangles" << endl;
      continue;
    }
    int c = 0;
    ostringstream oss;
    do {
      P r[] = {ps[a[0]], ps[a[1]], ps[a[2]], ps[a[3]]};
      if (rectp(r)) {
        if (c % 10 == 0) {
          oss << endl;
        }
        ++c;
        oss << " " << cs[a[0]] << cs[a[1]] << cs[a[2]] << cs[a[3]];
      }
      reverse(a.begin()+4, a.end());
    } while (next_permutation(a.begin(), a.end()));
    if (c == 0) {
      cout << " No rectangles" << endl;
    } else {
      cout << oss.str() << endl;
    }
  }
  return 0;
}