#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct cmp
{
  bool operator()(const vector<string>& lhs, const vector<string>& rhs) const
  {
    if (lhs.size() != rhs.size()) {
      return lhs.size() > rhs.size();
    } else {
      return lhs < rhs;
    }
  }
};

int main()
{
  map<string,int> m;
  vector<vector<string> > v;
  string word;
  while (getline(cin, word)) {
    string w(word);
    sort(w.begin(), w.end());
    const map<string,int>::const_iterator it = m.find(w);
    if (it == m.end()) {
      const int id = m.size();
      m.insert(make_pair(w, id));
      v.push_back(vector<string>(1, word));
    } else {
      v[it->second].push_back(word);
    }
  }
  for (vector<vector<string> >::iterator it(v.begin()); it != v.end(); ++it) {
    sort(it->begin(), it->end());
  }
  sort(v.begin(), v.end(), cmp());
  const int len = min(5, int(v.size()));
  for (int i = 0; i < len; i++) {
    cout << "Group of size " << v[i].size() << ": ";
    vector<string>::iterator last = unique(v[i].begin(), v[i].end());
    for (vector<string>::const_iterator it(v[i].begin()); it != last; ++it) {
      cout << *it << ' ';
    }
    cout << "." << endl;
  }
  return 0;
}
