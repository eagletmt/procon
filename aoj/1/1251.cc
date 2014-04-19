#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;

struct not_found {};

string join(const vector<string>& v)
{
  string s = "";
  for (vector<string>::const_iterator it(v.begin()); it != v.end(); ++it) {
    s += "/" + *it;
  }
  return s;
}

string expand(const set<string>& s, string path)
{
  vector<string> parts;
  string::iterator it = path.begin()+1;
  string base;
  while (true) {
    string::iterator jt = find(it, path.end(), '/');
    if (jt == path.end()) {
      base = string(it, jt);
      break;
    }
    parts.push_back(string(it, jt));
    it = jt+1;
  }

  vector<string> ans;
  for (vector<string>::const_iterator jt(parts.begin()); jt != parts.end(); ++jt) {
    if (*jt == ".") {
    } else if (*jt == "..") {
      ans.pop_back();
    } else {
      ans.push_back(*jt);
    }
    if (!s.count(join(ans) + "/")) {
      throw not_found();
    }
  }
  if (base == ".") {
    base = "";
  } else if (base == "..") {
    if (ans.empty()) {
      throw not_found();
    }
    base = "";
    ans.pop_back();
  }

  string dir = join(ans);
  //cerr << "dir=" << dir << ", base=" << base << endl;
  if (s.count(dir+"/"+base+"/")) {
    dir += "/"+base;
    base = "";
  }
  if (base.empty()) {
    base = "index.html";
  }
  string a = dir+"/"+base;
  if (!s.count(a)) {
    throw not_found();
  }
  return a;
}

int main()
{
  int N, M;
  while (cin >> N >> M && N != 0) {
    set<string> s;
    for (int i = 0; i < N; i++) {
      string t;
      cin >> t;
      for (string::iterator it = t.begin(); it != t.end(); ++it) {
        if (*it == '/') {
          s.insert(string(t.begin(), it) + "/");
        }
      }
      s.insert(t);
    }

    for (int i = 0; i < M; i++) {
      string s1, s2;
      cin >> s1 >> s2;
      try {
        cout << (expand(s, s1) == expand(s, s2) ? "yes" : "no") << endl;
      } catch (const not_found&) {
        cout << "not found" << endl;
      }
    }
  }
  return 0;
}
