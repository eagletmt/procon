#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
  int N, M, K;
  cin >> N >> M >> K;
  vector<int> v(K);
  for (int i = 0; i < K; i++) {
    cin >> v[i];
  }
  int ans = 0;
  for (int i = 0; i < K; i++) {
    int x;
    cin >> x;
    ans += abs(x - v[i]);
  }
  cout << ans/2 << endl;
  return 0;
}