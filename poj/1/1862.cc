#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <cmath>
using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<double> v(N);
  copy(istream_iterator<double>(cin), istream_iterator<double>(), v.begin());
  sort(v.begin(), v.end(), greater<double>());
  for (int i = 0; i < N-1; i++) {
    v[i+1] = 2*sqrt(v[i]*v[i+1]);
  }
  cout << fixed;
  cout.precision(3);
  cout << v.back() << endl;
  return 0;
}
