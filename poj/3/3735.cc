#include <iostream>
using namespace std;

typedef long long elem_type;
static const int N = 101;

void matrix_mult(elem_type c[N][N], const elem_type a[N][N], const elem_type b[N][N], int n)
{
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      c[i][j] = 0;
      for (int k = 0; k < n; k++) {
        if (a[i][k] && b[k][j]) {
          c[i][j] += a[i][k] * b[k][j];
        }
      }
    }
  }
}

void matrix_power(elem_type c[N][N], const elem_type a[N][N], int n, int e)
{
  if (e == 0) {
    for (int i = 0; i < n; i++) {
      c[i][i] = 1;
    }
  } else if (e == 1) {
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        c[i][j] = a[i][j];
      }
    }
  } else if (e % 2 == 0) {
    elem_type b[N][N];
    matrix_power(b, a, n, e/2);
    matrix_mult(c, b, b, n);
  } else {
    elem_type b[N][N];
    matrix_power(b, a, n, e-1);
    matrix_mult(c, a, b, n);
  }
}

int main()
{
  int n, k;
  long long m;
  elem_type matrix[N][N], r[N][N];
  while (cin >> n >> m >> k && !(n == 0 && m == 0 && k == 0)) {
    for (int i = 0; i <= n; i++) {
      for (int j = 0; j <= n; j++) {
        matrix[i][j] = i == j;
      }
    }

    for (int i = 0; i < k; i++) {
      char c;
      int x;
      cin >> c >> x;
      x--;
      if (c == 'g') {
        matrix[x][n]++;
      } else if (c == 'e') {
        fill(matrix[x], matrix[x]+n+1, 0);
      } else {
        int y;
        cin >> y;
        y--;
        swap(matrix[x], matrix[y]);
      }
    }

    matrix_power(r, matrix, n+1, m);
    for (int i = 0; i < n; i++) {
      if (i) {
        cout << ' ';
      }
      cout << r[i][n];
    }
    cout << endl;
  }
  return 0;
}
