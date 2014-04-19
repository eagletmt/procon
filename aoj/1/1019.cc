#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

int main()
{
  int N, K;
  while (cin >> N >> K && N != 0) {
    vector<int> s(K);
    for (int i = 0; i < K; i++) {
      cin >> s[i];
    }
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < K; j++) {
        int x;
        cin >> x;
        s[j] -= x;
      }
    }
    if (find_if(s.begin(), s.end(), bind2nd(less<int>(), 0)) == s.end()) {
      cout << "Yes" << endl;
    } else {
      cout << "No" << endl;
    }
  }
  return 0;
}
