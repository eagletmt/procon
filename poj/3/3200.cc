#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<double> P;

struct block {
  double r;
  P p;
};

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<block> blocks(N);
    for (int i = 0; i < N; i++) {
      cin >> blocks[i].p.real() >> blocks[i].p.imag() >> blocks[i].r;
    }

    for (int i = 1; i < N; i++) {
      double m = blocks[i].r * blocks[i].r;
      double sum_x = blocks[i].p.real() * m;
      double sum_y = blocks[i].p.imag() * m;
      for (int j = i-1; j >= 0; j--) {
        const P p(sum_x / m, sum_y / m);
        if (abs(p - blocks[j].p)*abs(p - blocks[j].p) >= blocks[j].r*blocks[j].r) {
          cout << "Unfeasible " << i << endl;
          goto NEXT;
        }
        m += blocks[j].r * blocks[j].r;
        sum_x += blocks[j].p.real() * blocks[j].r * blocks[j].r;
        sum_y += blocks[j].p.imag() * blocks[j].r * blocks[j].r;
      }
    }
    cout << "Feasible" << endl;
NEXT:
    ;
  }
  return 0;
}