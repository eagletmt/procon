#include <iostream>
#include <vector>
using namespace std;
static const int tbl[] = {10, 50, 100, 500};

vector<int> solve(int n)
{
  vector<int> v(4);
  for (int i = 3; i >= 0; i--) {
    v[i] = n / tbl[i];
    n %= tbl[i];
  }
  return v;
}

int main()
{
  bool first = true;
  int N;
  while (cin >> N && N != 0) {
    vector<int> v(4);
    int s = 0;
    for (int i = 0; i < 4; i++) {
      cin >> v[i];
      s += v[i] * tbl[i];
    }

    const vector<int> w = solve(s - N);
    if (!first) {
      cout << endl;
    }
    for (int i = 0; i < 4; i++) {
      if (v[i] > w[i]) {
        cout << tbl[i] << ' ' << v[i] - w[i] << endl;
      }
    }
    first = false;
  }
  return 0;
}
