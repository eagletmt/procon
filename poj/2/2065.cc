#include <iostream>
#include <vector>
using namespace std;

struct mod/*{{{*/
{
  int m;
  vector<int> tbl;
  mod(int a) : m(a), tbl(m+1)
  {
    for (int x = 1; x < m; x++) {
      tbl[x] = pow(x, a-2);
    }
  }
  int pow(int x, int e)
  {
    if (e == 0) {
      return 1;
    } else if (e & 1) {
      return (x * pow(x, e-1))%m;
    } else {
      const int y = pow(x, e>>1);
      return (y*y)%m;
    }
  }
  int operator()(int x) const { return ((x%m)+m)%m; }
  int inv(int x) const { return tbl[x]; }
};/*}}}*/

template <class T>
bool gaussian_elimination(vector<vector<T> >& a, vector<T>& b, const mod& MOD)/*{{{*/
{
  const int N = a.size();
  const int M = a[0].size();
  // assert(N >= M)

  for (int i = 0, p = 0; i < M; i++, p++) {
    int q;
    for (q = p; q < N && a[q][i] == 0; q++);
    if (q == N) {
      --p;
      continue;
    }
    swap(a[i], a[q]);
    swap(b[i], b[q]);

    const T r = MOD.inv(a[i][i]);
    for (int k = i; k < M; k++) {
      a[i][k] = MOD(a[i][k] * r);
    }
    b[i] = MOD(b[i] * r);

    for (int j = 0; j < N; j++) {
      if (j == i) {
        continue;
      }
      const T t = a[j][i];
      for (int k = i; k < M; k++) {
        a[j][k] = MOD(a[j][k] - t * a[i][k]);
      }
      b[j] = MOD(b[j] - t * b[i]);
    }
  }

  for (int i = 0; i < M; i++) {
    if (a[i][i] == 0 && b[i] != 0) {
      // no solution
      return false;
    }
  }
  return true;
}/*}}}*/

int main()
{
  ios::sync_with_stdio(false);
  int T;
  cin >> T;
  while (T-- > 0) {
    int p;
    cin >> p;
    string s;
    cin >> s;
    const int N = s.size();
    mod m(p);
    vector<vector<int> > mat(N, vector<int>(N));
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        mat[i][j] = m.pow(i+1, j);
      }
      if (s[i] == '*') {
        b[i] = 0;
      } else {
        b[i] = s[i]-'a'+1;
      }
    }

    gaussian_elimination(mat, b, m);
    for (vector<int>::const_iterator it = b.begin(); it != b.end(); ++it) {
      if (it != b.begin()) {
        cout << " ";
      }
      cout << *it;
    }
    cout << endl;
  }
  return 0;
}