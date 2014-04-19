#include <iostream>
#include <vector>
#include <map>
using namespace std;

vector<vector<int> > mul(const vector<vector<int> >& m, const vector<vector<int> >& n)
{
  const int N = m.size();
  vector<vector<int> > r(N, vector<int>(N, false));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < N; j++) {
      for (int k = 0; k < N; k++) {
        r[i][j] = r[i][j] ^ (m[i][k] && n[k][j]);
      }
    }
  }
  return r;
}

vector<vector<int> > pow(const vector<vector<int> >& mat, long long e)
{
  if (e == 0) {
    const int N = mat.size();
    vector<vector<int> > m(N, vector<int>(N, false));
    for (int i = 0; i < N; i++) {
      m[i][i] = true;
    }
    return m;
  } else if (e % 2 == 0) {
    const vector<vector<int> > m = pow(mat, e/2);
    return mul(m, m);
  } else {
    return mul(mat, pow(mat, e-1));
  }
}

int numbering(map<string,int>& m, const string& name)
{
  const map<string,int>::const_iterator it = m.find(name);
  if (it == m.end()) {
    const int i = m.size();
    m.insert(make_pair(name, i));
    return i;
  } else {
    return it->second;
  }
}

int main()
{
  int X;
  for (cin >> X; X > 0; X--) {
    int N;
    long long T;
    cin >> N >> T;
    vector<vector<int> > m(N, vector<int>(N, false));
    for (int i = 0; i < N; i++) {
      m[i][i] = true;
    }
    vector<int> v(N);
    map<string,int> m2i;
    for (int i = 0; i < N; i++) {
      int x, n;
      string name;
      cin >> name >> x >> n;
      const int id0 = numbering(m2i, name);
      v[id0] = x % 2 != 0;
      for (int j = 0; j < n; j++) {
        cin >> name;
        const int id1 = numbering(m2i, name);
        m[id1][id0] = m[id1][id0] ^ true;
      }
    }
    m = pow(m, T-1);
    int ans = 0;
    for (int i = 0; i < N; i++) {
      bool b = false;
      for (int j = 0; j < N; j++) {
        b = b ^ (m[i][j] && v[j]);
      }
      if (b) {
        ++ans;
      }
    }
    cout << ans << endl;
  }
  return 0;
}