#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int unsortedness(string str)
{
  int c = 0;
  for (string::size_type i = 0; i < str.size()-1; i++) {
    for (string::size_type j = str.size()-1; j > i; j--) {
      if (str[j-1] > str[j]) {
        swap(str[j-1], str[j]);
        ++c;
      }
    }
  }
  return c;
}

int main()
{
  int N, M;
  cin >> N >> M;
  vector<pair<int,string> > v;
  v.reserve(M);
  for (int i = 0; i < M; i++) {
    string dna;
    cin >> dna;
    v.push_back(make_pair(unsortedness(dna), dna));
  }
  stable_sort(v.begin(), v.end());
  for (vector<pair<int,string> >::const_iterator it(v.begin()); it != v.end(); ++it) {
    cout << it->second << endl;
  }
  return 0;
}