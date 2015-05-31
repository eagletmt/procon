#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include <future>
using namespace std;

int solve(const vector<vector<int> >& sentences)
{
  vector<int> english(sentences[0]), french(sentences[1]);

  const int N = sentences.size() - 2;
  if (N == 0) {
    int ans = 0;
    for (int w : english) {
      auto it = lower_bound(french.begin(), french.end(), w);
      if (it != french.end() && *it == w) {
        ++ans;
      }
    }
    return ans;
  }

  int ans = 10000000;
  for (unsigned s = 0; s < (1U<<N); s++) {
    vector<int> e(english), f(french);

    for (int i = 0; i < N; i++) {
      if (s & (1u<<i)) {
        for (int w : sentences[i+2]) {
          e.push_back(w);
        }
      } else {
        for (int w : sentences[i+2]) {
          f.push_back(w);
        }
      }
    }

    sort(e.begin(), e.end());
    e.erase(unique(e.begin(), e.end()), e.end());
    sort(f.begin(), f.end());
    f.erase(unique(f.begin(), f.end()), f.end());
    int c = 0;
    for (int w : e) {
      auto it = lower_bound(f.begin(), f.end(), w);
      if (it != f.end() && *it == w) {
        ++c;
      }
    }
    ans = min(ans, c);
  }

  return ans;
}

int main()
{
  string s;
  getline(cin, s);
  int T;
  {
    istringstream iss(s);
    iss >> T;
  }

  vector<future<int> > fs;
  for (int Ti = 1; Ti <= T; Ti++) {
    getline(cin, s);
    int N;
    {
      istringstream iss(s);
      iss >> N;
    }
    vector<vector<int> > sentences;
    map<string,int> m;
    for (int i = 0; i < N; i++) {
      getline(cin, s);
      istringstream iss(s);
      vector<int> v;
      for (string w; iss >> w; ) {
        if (!m.count(w)) {
          int id = m.size();
          m[w] = id;
        }
        v.push_back(m[w]);
      }
      sort(v.begin(), v.end());
      v.erase(unique(v.begin(), v.end()), v.end());
      sentences.push_back(v);
    }

    fs.push_back(async(std::launch::async, solve, sentences));
  }

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": " << fs[Ti-1].get() << endl;
  }
  return 0;
}
