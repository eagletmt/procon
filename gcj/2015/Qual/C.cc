#include <iostream>
#include <vector>
using namespace std;

enum quaternion { E, I, J, K, N_E, N_I, N_J, N_K };

const quaternion MUL_TABLE[8][8] = {
  { E, I, J, K,
    N_E, N_I, N_J, N_K },
  { I, N_E, K, N_J,
    N_I, E, N_K, J },
  { J, N_K, N_E, I,
    N_J, K, E, N_I },
  { K, J, N_I, N_E,
    N_K, N_J, I, E },

  { N_E, N_I, N_J, N_K,
    E, I, J, K },
  { N_I, E, N_K, J,
    I, N_E, K, N_J },
  { N_J, K, E, N_I,
    J, N_K, N_E, I },
  { N_K, N_J, I, E,
    K, J, N_I, N_E },
};
const string STRING_TABLE[8] = {
  "1", "i", "j", "k",
  "-1", "-i", "-j", "-k",
};

quaternion operator*(quaternion x, quaternion y)
{
  return MUL_TABLE[int(x)][int(y)];
}

ostream& operator<<(ostream& os, quaternion x)
{
  return os << STRING_TABLE[int(x)];
}

quaternion parse(char c)
{
  switch (c) {
    case '1':
      return E;
    case 'i':
      return I;
    case 'j':
      return J;
    case 'k':
      return K;
    default:
      throw __LINE__;
  }
}

quaternion pow(quaternion x, long long n)
{
  if (n == 1) {
    return x;
  } else if (n % 2 == 0) {
    quaternion y = pow(x, n/2);
    return y * y;
  } else {
    return x * pow(x, n-1);
  }
}

quaternion total_product(int L, long long X, const vector<quaternion>& qs)
{
  quaternion p = E;
  for (int i = 0; i < L; i++) {
    p = p * qs[i];
  }
  return pow(p, X);
}

bool solve_k(int L, long long X, const vector<quaternion>& qs, int i)
{
  quaternion r = E;

  for (int k = 0; k < 4*L; k++) {
    r = qs[L - (k % L) - 1] * r;
    if (r == K) {
      if (static_cast<long long>(i+1 + k+1) <= L*X) {
        return true;
      }
    }
  }
  return false;
}

bool solve(int L, long long X, const vector<quaternion>& qs)
{
  if (total_product(L, X, qs) != N_E) {
    return false;
  }

  quaternion l = E;
  for (int i = 0; i < 4*L; i++) {
    l = l * qs[i % L];
    if (l == I) {
      if (solve_k(L, X, qs, i)) {
        return true;
      }
    }
  }
  return false;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int L;
    long long X;
    cin >> L >> X;
    string s;
    cin >> s;
    vector<quaternion> qs;
    for (int i = 0; i < L; i++) {
      qs.push_back(parse(s[i]));
    }
    cout << "Case #" << Ti << ": " << (solve(L, X, qs) ? "YES" : "NO") << endl;
  }
  return 0;
}
