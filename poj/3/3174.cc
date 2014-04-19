#include <iostream>
#include <vector>
#include <complex>
using namespace std;
typedef complex<int> P;

int main()
{
  int N;
  cin >> N;
  vector<P> v(N);
  for (int i = 0; i < N; i++) {
    cin >> v[i].real() >> v[i].imag();
  }

  vector<pair<int,pair<int,int> > > ans;
  for (int i = 0; i < N; i++) {
    for (int j = i+1; j < N; j++) {
      for (int k = j+1; k < N; k++) {
        if ((v[i] - v[j]).real() * (v[j] - v[k]).imag() == (v[i] - v[j]).imag() * (v[j] - v[k]).real()) {
          ans.push_back(make_pair(i+1, make_pair(j+1, k+1)));
        }
      }
    }
  }

  cout << ans.size() << endl;
  for (vector<pair<int,pair<int,int> > >::const_iterator it(ans.begin()); it != ans.end(); ++it) {
    cout << it->first << ' ' << it->second.first << ' ' << it->second.second << endl;
  }
  return 0;
}
