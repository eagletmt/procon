#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct tree {
  bool is_leaf;
  int idx;
  int value;
  vector<tree> children;
  tree() {}
  tree(int i) : is_leaf(true), idx(i) {}
  tree(const tree& l, const tree& r) : is_leaf(false), children(2)
  {
    children[0] = l;
    children[1] = r;
  }

  tree left() const { return children[0]; }
  tree right() const { return children[1]; }
};

pair<tree,int> parse(const string& s, int start = 0)
{
  if (s[start] == '(') {
    pair<tree,int> left = parse(s, start+1);
    pair<tree,int> right = parse(s, left.second+1);
    return make_pair(tree(left.first, right.first), right.second+1);
  } else {
    return make_pair(tree(s[start]-'1'), start+1);
  }
}

vector<int> evals(const tree& t, vector<int> binds)
{
  if (t.is_leaf) {
    return vector<int>(1, binds[t.idx]);
  } else {
    const vector<int> l = evals(t.left(), binds);
    const vector<int> r = evals(t.right(), binds);
    vector<int> ret;
    for (vector<int>::const_iterator it(l.begin()); it != l.end(); ++it) {
      for (vector<int>::const_iterator jt(r.begin()); jt != r.end(); ++jt) {
        ret.push_back(*it & *jt);
        ret.push_back(*it | *jt);
        ret.push_back(*it ^ *jt);
      }
    }
    return ret;
  }
}

void print(const tree& t)
{
  if (t.is_leaf) {
    cout << t.idx;
  } else {
    cout << '(';
    print(t.children[0]);
    cout << ' ';
    print(t.children[1]);
    cout << ')';
  }
}

int main()
{
  string s;
  while (getline(cin, s) && s != "END") {
    pair<tree,int> p = parse(s);
    getline(cin, s);
    int N = s[0]-'0';
    vector<int> b(N);
    for (int i = 0; i < N; i++) {
      getline(cin, s);
      int v = 0;
      for (int j = 0; j < 4; j++) {
        int a = s[j*2]-'0';
        v = (v<<1) | a;
      }
      b[i] = v;
    }

    int ans = 0;
    vector<int> r = evals(p.first, b);
    for (vector<int>::const_iterator it(r.begin()); it != r.end(); ++it) {
      if (*it == 15) {
        ans++;
      }
    }
    cout << ans << endl;
  }
  return 0;
}
