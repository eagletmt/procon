#define NDEBUG
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
using namespace std;

typedef long long ll;
const ll MOD = 1000000009;

vector<vector<ll> > mat_mul(const vector<vector<ll> >& m1, const vector<vector<ll> >& m2)
{
  const int N = m1.size(), K = m2.size(), M = m2[0].size();
  assert(int(m1[0].size()) == K);
  vector<vector<ll> > r(N, vector<ll>(M));
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      r[i][j] = 0;
      for (int k = 0; k < K; k++) {
        r[i][j] = (r[i][j] + m1[i][k] * m2[k][j]) % MOD;
      }
    }
  }
  return r;
}

vector<ll> mat_mul(const vector<vector<ll> >& m, const vector<ll>& v)
{
  const int N = m.size(), M = m[0].size();
  assert(int(v.size()) == M);
  vector<ll> r(N);
  for (int i = 0; i < N; i++) {
    r[i] = 0;
    for (int j = 0; j < M; j++) {
      r[i] = (r[i] + m[i][j] * v[j]) % MOD;
    }
  }
  return r;
}

vector<vector<ll> > mat_pow(const vector<vector<ll> >& m, ll e)
{
  const int N = m.size();
  assert(int(m[0].size()) == N);
  if (e == 0) {
    vector<vector<ll> > id(N, vector<ll>(N, 0));
    for (int i = 0; i < N; i++) {
      id[i][i] = 1;
    }
    return id;
  } else if (e & 1) {
    return mat_mul(m, mat_pow(m, e-1));
  } else {
    const vector<vector<ll> > mm = mat_pow(m, e>>1);
    return mat_mul(mm, mm);
  }
}

int main()
{
  ll W, H, N;
  for (int Ti = 1; cin >> W >> H >> N && W != 0; Ti++) {
    multimap<ll, int> obstacles;
    vector<ll> hs;
    for (int i = 0; i < N; i++) {
      int w;
      ll h;
      cin >> w >> h;
      --w;
      --h;
      obstacles.insert(make_pair(h, w));
      hs.push_back(h);
    }
    hs.push_back(H-1);
    sort(hs.begin(), hs.end());
    hs.erase(unique(hs.begin(), hs.end()), hs.end());

    vector<ll> row(W, 0);
    row[0] = 1;
    vector<vector<ll> > trans(W, vector<ll>(W, 0));
    for (int i = 0; i < W; i++) {
      for (int k = -1; k <= 1; k++) {
        const int j = i + k;
        if (0 <= j && j < W) {
          trans[i][j] = 1;
        }
      }
    }

    ll h = 0;
    for (vector<ll>::const_iterator it = hs.begin(); it != hs.end(); ++it) {
      const vector<vector<ll> > t = mat_pow(trans, *it - h);
      row = mat_mul(t, row);
      typedef multimap<ll, int>::const_iterator Iterator;
      const pair<Iterator, Iterator> p = obstacles.equal_range(*it);
      for (Iterator jt = p.first; jt != p.second; ++jt) {
        row[jt->second] = 0;
      }
      h = *it;
    }

    cout << "Case " << Ti << ": " << row[W-1] << endl;
  }
  return 0;
}
