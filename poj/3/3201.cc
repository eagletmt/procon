#include <iostream>
#include <vector>
#include <stdexcept>
#include <utility>
#include <iterator>
using namespace std;

static char tbl[0x80];

class interpret_error {};

pair<vector<string>,int> interpret(const string& src, int start = 0) throw(interpret_error)
{
  if (src[start] == 'A') {
    vector<string> v(2);
    v[0] = "//";  v[1] = "/+";
    return make_pair(v, start+1);
  } else if (src[start] == 'B') {
    return make_pair(vector<string>(2, "--"), start+1);
  } else if (src[start] == 't') {
    // turn
    const pair<vector<string>,int> a(interpret(src, start+5));
    const vector<string>& q = a.first;
    vector<string> turned(q[0].size(), string(q.size(), ' '));
    for (vector<string>::size_type i = 0; i < q.size(); i++) {
      for (string::size_type j = 0; j < q[0].size(); j++) {
        turned[j][q.size()-i-1] = tbl[q[i][j]];
      }
    }
    return make_pair(turned, a.second+1);
  } else if (src[start] == 's') {
    // sew
    pair<vector<string>,int> a(interpret(src, start+4));
    const pair<vector<string>,int> b(interpret(src, a.second+1));
    vector<string>& left = a.first;
    const vector<string>& right = b.first;
    if (left.size() != right.size()) {
      throw interpret_error();
    }
    for (vector<string>::size_type i = 0; i < right.size(); i++) {
      left[i] += right[i];
    }
    return make_pair(left, b.second+1);
  }
}

int main()
{
  tbl['/'] = '\\';
  tbl['\\'] = '/';
  tbl['+'] = '+';
  tbl['-'] = '|';
  tbl['|'] = '-';

  string src, s;
  int count = 0;
  while (cin >> s) {
    for (;;) {
      const string::size_type i = s.find_first_of(';');
      if (i == string::npos) {
        src += s;
        break;
      } else {
        src += s.substr(0, i);
        cout << "Quilt " << ++count << ":" << endl;
        try {
          const vector<string> quilt = interpret(src).first;
          copy(quilt.begin(), quilt.end(), ostream_iterator<string>(cout, "\n"));
        } catch (const interpret_error&) {
          cout << "error" << endl;
        }
        src = "";
        s = s.substr(i+1);
      }
    }
  }
  return 0;
}