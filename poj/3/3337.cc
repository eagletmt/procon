#include <iostream>
#include <sstream>
#include <vector>
#include <cctype>
#include <map>
using namespace std;

map<char,int> init_vartable(const string& s)/*{{{*/
{
  map<char,int> m;
  for (string::const_iterator it(s.begin()); it != s.end(); ++it) {
    if (isalpha(*it)) {
      m.insert(make_pair(*it, *it-'a'+1));
    }
  }
  return m;
}/*}}}*/

string strip(const string& s)/*{{{*/
{
  string ret;
  for (string::const_iterator it(s.begin()); it != s.end(); ++it) {
    if (*it != ' ') {
      ret += *it;
    }
  }
  return ret;
}/*}}}*/

string preop(const string& s, map<char,int>& m)/*{{{*/
{
  string ret;
  string::const_iterator it = s.begin();
  while (it+2 != s.end() && it+1 != s.end() && it != s.end()) {
    if (*it == '+' && *(it+1) == '+' && isalpha(*(it+2))) {
      // ++a
      ret += *(it+2);
      ++m[*(it+2)];
      it = it+3;
    } else if (*it == '-' && *(it+1) == '-' && isalpha(*(it+2))) {
      // --a
      ret += *(it+2);
      --m[*(it+2)];
      it = it+3;
    } else {
      ret += *it;
      ++it;
    }
  }
  ret += string(it, s.end());
  return ret;
}/*}}}*/

pair<string,pair<vector<char>,vector<char> > >
postop(const string& s)/*{{{*/
{
  string ret;
  vector<char> incs, decs;
  string::const_iterator it = s.begin();
  while (it+2 != s.end() && it+1 != s.end() && it != s.end()) {
    if (isalpha(*it) && *(it+1) == '+' && *(it+2) == '+') {
      // a++
      ret += *it;
      incs.push_back(*it);
      it = it+3;
    } else if (isalpha(*it) && *(it+1) == '-' && *(it+2) == '-') {
      // a--
      ret += *it;
      decs.push_back(*it);
      it = it+3;
    } else {
      ret += *it;
      ++it;
    }
  }
  ret += string(it, s.end());
  return make_pair(ret, make_pair(incs, decs));
}/*}}}*/

int eval(const string& expr, const map<char,int>& m)/*{{{*/
{
  string::const_iterator it = expr.begin();
  int val = m.find(*it)->second;
  ++it;
  while (it != expr.end()) {
    if (*it == '+') {
      ++it;
      val += m.find(*it)->second;
    } else if (*it == '-') {
      ++it;
      val -= m.find(*it)->second;
    } else {
      cerr << "UNEXPECTED" << endl;
      while (1) {}
    }
    ++it;
  }
  return val;
}/*}}}*/

void do_postop(const vector<char>& incs, const vector<char>& decs, map<char,int>& m)/*{{{*/
{
  for (vector<char>::const_iterator it(incs.begin()); it != incs.end(); ++it) {
    ++m[*it];
  }
  for (vector<char>::const_iterator it(decs.begin()); it != decs.end(); ++it) {
    --m[*it];
  }
}/*}}}*/

pair<int,map<char,int> > solve(const string& input)/*{{{*/
{
  const string s = strip(input);
  map<char,int> m = init_vartable(s);
  const string t = preop(s, m);
  const pair<string,pair<vector<char>,vector<char> > > u = postop(t);
  const int val = eval(u.first, m);
  do_postop(u.second.first, u.second.second, m);
  return make_pair(val, m);
}/*}}}*/

int main()
{
  string s;
  getline(cin, s);
  istringstream iss(s);
  int T;
  iss >> T;
  while (T-- > 0) {
    getline(cin, s);
    pair<int,map<char,int> > r = solve(s);
    cout << "Expression: " << s << endl;
    cout << "value = " << r.first << endl;
    for (map<char,int>::const_iterator it = r.second.begin(); it != r.second.end(); ++it) {
      cout << it->first << " = " << it->second << endl;
    }
  }
  return 0;
}