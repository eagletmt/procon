#include <iostream>
#include <vector>
#include <cstdlib>
#include <iterator>
#include <functional>
#include <algorithm>
#include <numeric>
using namespace std;

struct abs_diff : binary_function<int,int,int> {
  int operator()(int a, int b) const
  {
    return abs(a - b);
  }
};

struct not_jolly_p : binary_function<int, int, bool> {
  int operator()(int a, int b) const {
    return b-a != 1;
  }
};

int main()
{
  int n;
  while (cin >> n) {
    vector<int> seq(n);
    for (vector<int>::iterator it(seq.begin()); it != seq.end(); ++it) {
      cin >> *it;
    }
    vector<int> diffs(n);
    adjacent_difference(seq.begin(), seq.end(), diffs.begin(), abs_diff());
    sort(diffs.begin()+1, diffs.end());
    
    vector<int>::const_iterator jt(adjacent_find(diffs.begin()+1, diffs.end(), not_jolly_p()));
    cout << (jt == diffs.end() ? "Jolly" : "Not jolly") << endl;
  }

  return 0;
}
