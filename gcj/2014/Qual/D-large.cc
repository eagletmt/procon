#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int war(vector<int>& naomi, vector<int> ken)
{
  int naomi_won = 0;
  for (vector<int>::const_iterator it = naomi.begin(); it != naomi.end(); ++it) {
    vector<int>::iterator jt = lower_bound(ken.begin(), ken.end(), *it);
    if (jt == ken.end()) {
      jt = ken.begin();
    }
    if (*jt < *it) {
      ++naomi_won;
    }
    ken.erase(jt);
  }
  return naomi_won;
}

int deceitful(const vector<int>& naomi, const vector<int>& ken)
{
  const int N = naomi.size();
  int j = 0;
  for (int i = 0; i < N; i++) {
    if (naomi[i] > ken[j]) {
      ++j;
    }
  }
  return j;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int N;
    cin >> N;
    vector<int> naomi, ken;
    for (int i = 0; i < N; i++) {
      double x;
      cin >> x;
      naomi.push_back(x * 1e5);
    }
    for (int i = 0; i < N; i++) {
      double x;
      cin >> x;
      ken.push_back(x * 1e5);
    }

    sort(naomi.begin(), naomi.end());
    sort(ken.begin(), ken.end());
    const int ans1 = deceitful(naomi, ken);
    const int ans2 = war(naomi, ken);
    cout << "Case #" << Ti << ": " << ans1 << " " << ans2 << endl;
  }
  return 0;
}
