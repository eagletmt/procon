#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n, k, m;
  while (cin >> n >> k >> m && n != 0) {
    --m;
    vector<int> v(n);
    for (int i = 0; i < n; i++) {
      v[i] = i+1;
    }

    for (int c = 0; c < n-1; c++) {
      v.erase(v.begin()+m);
      m = (m-1 + k) % v.size();
    }
    cout << v.front() << endl;
  }
  return 0;
}
