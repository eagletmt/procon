#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

int main()
{
  int N;
  cin >> N;
  vector<int> v(N);
  copy(istream_iterator<int>(cin), istream_iterator<int>(), v.begin());
  sort(v.begin(), v.end());
  cout << v[(N-1)/2] << endl;
  return 0;
}
