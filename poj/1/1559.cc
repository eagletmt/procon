#include <iostream>
#include <vector>
#include <sstream>
#include <algorithm>
using namespace std;

pair<string,string> lex_number(string str)
{
  string::size_type i = 0;
  if (str[0] == '+') {
    str = str.substr(1);
  } else if (str[0] == '-') {
    i++;
  }
  while (i < str.size() && '0' <= str[i] && str[i] <= '9') {
    i++;
  }
  return make_pair(str.substr(0, i), str.substr(i));
}

vector<string> lex_op(const string& str)
{
  static const string ops = "+-*/";
  pair<string,string> p = lex_number(str);
  vector<string> tokens(1, p.first);
  string rest = p.second;
  while (!rest.empty() && ops.find(rest[0]) != string::npos) {
    tokens.push_back(string(1, rest[0]));
    p = lex_number(rest.substr(1));
    tokens.push_back(p.first);
    rest = p.second;
  }
  return tokens;
}

int to_i(const string& s)
{
  istringstream iss(s);
  int n;
  iss >> n;
  return n;
}

string to_s(int n)
{
  ostringstream oss;
  oss << n;
  return oss.str();
}

bool muldiv(vector<string>& tokens)
{
  vector<string> r;
  for (vector<string>::const_iterator it(tokens.begin()); it != tokens.end(); ++it) {
    if (*it == "*" || *it == "/") {
      const char op = it->at(0);
      ++it;
      const int x = to_i(r.back()), y = to_i(*it);
      r.back() = to_s(op == '*' ? x*y : x/y);
      ++it;
      while (it != tokens.end()) {
        r.push_back(*it);
        ++it;
      }
      tokens = r;
      return true;
    } else {
      r.push_back(*it);
    }
  }
  return false;
}

bool addsub(vector<string>& tokens)
{
  vector<string> r;
  for (vector<string>::const_iterator it(tokens.begin()); it != tokens.end(); ++it) {
    if (*it == "+" || *it == "-") {
      const char op = it->at(0);
      ++it;
      const int x = to_i(r.back()), y = to_i(*it);
      r.back() = to_s(op == '+' ? x+y : x-y);
      ++it;
      while (it != tokens.end()) {
        r.push_back(*it);
        ++it;
      }
      tokens = r;
      return true;
    } else {
      r.push_back(*it);
    }
  }
  return false;
}

void display(const vector<string>& tokens, const string& rhs)
{
  for (vector<string>::const_iterator it(tokens.begin()); it != tokens.end(); ++it) {
    if (it != tokens.begin()) {
      cout << ' ';
    }
    cout << *it;
  }
  cout << " = " << rhs << endl;
}

int main()
{
  string line;
  while (getline(cin, line)) {
    line.erase(remove(line.begin(), line.end(), ' '), line.end());
    const string::size_type i = line.find('=');
    const string rhs = line.substr(i+1);
    vector<string> tokens = lex_op(line.substr(0, i));

    display(tokens, rhs);
    while (muldiv(tokens)) {
      display(tokens, rhs);
    }
    while (addsub(tokens)) {
      display(tokens, rhs);
    }
    cout << endl;
  }
  return 0;
}