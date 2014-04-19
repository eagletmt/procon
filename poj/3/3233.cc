#include <iostream>
#include <vector>
using namespace std;

template <typename T>
class MatrixMod {
  private:
    vector<vector<T> > rows;
    int mod;

  public:
    MatrixMod(const vector<vector<T> >& r, int m) : rows(r), mod(m) {}
    MatrixMod(const MatrixMod<T>& m) : rows(m.rows), mod(m.mod) {}
    MatrixMod(int N, int m) : rows(N, vector<T>(N)), mod(m) {}

    static MatrixMod<T> identity(int n, int m)
    {
      MatrixMod<T> a(n, m);
      for (int i = 0; i < n; i++) {
        a[i][i] = 1;
      }
      return a;
    }

    int size() const
    {
      return rows.size();
    }

    const vector<T>& operator[](int i) const
    {
      return rows[i];
    }

    vector<T>& operator[](int i)
    {
      return rows[i];
    }

    MatrixMod<T> operator+(const MatrixMod<T>& rhs) const
    {
      const int N = rows.size();
      MatrixMod<T> ret(N, mod);
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          ret[i][j] = (rows[i][j] + rhs[i][j]) % mod;
        }
      }
      return ret;
    }

    MatrixMod<T> operator*(const MatrixMod<T>& rhs) const
    {
      const int N = rows.size();
      MatrixMod<T> ret(N, mod);
      for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
          ret[i][j] = 0;
          for (int k = 0; k < N; k++) {
            ret[i][j] = (ret[i][j] + rows[i][k] * rhs[k][j]) % mod;
          }
        }
      }
      return ret;
    }

    MatrixMod<T> operator^(int e) const
    {
      if (e == 1) {
        return *this;
      } else if (e % 2 == 0) {
        const MatrixMod<T> m(*this ^ (e/2));
        return m*m;
      } else {
        return *this * (*this ^ (e-1));
      }
    }
};

template <typename T>
MatrixMod<T> power_sum(const MatrixMod<T>& m, int k)
{
  if (k == 1) {
    return m;
  } else if (k % 2 == 0) {
    const MatrixMod<T> a(power_sum(m, k/2));
    const MatrixMod<T> b(m ^ (k/2));
    return a + a*b;
  } else {
    return (m^k) + power_sum(m, k-1);
  }
}

template <typename T>
void print(const MatrixMod<T>& a)
{
  const int n = a.size();
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (j) {
        cout << ' ';
      }
      cout << a[i][j];
    }
    cout << endl;
  }
}

int main()
{
  int n, k, m;
  cin >> n >> k >> m;
  MatrixMod<int> a(n, m);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      cin >> a[i][j];
      a[i][j] %= m;
    }
  }

  const MatrixMod<int> b(power_sum(a, k));
  print(b);

  return 0;
}
