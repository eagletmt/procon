#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef string::const_iterator Iterator;

bool eval_or(Iterator& it, const Iterator& last);
bool eval_factor(Iterator& it, const Iterator& last)
{
  if (*it == 'V') {
    ++it;
    return true;
  } else if (*it == 'F') {
    ++it;
    return false;
  } else if (*it == '(') {
    ++it;
    const bool r = eval_or(it, last);
    if (*it != ')') {
      throw "unmatched paren";
    }
    ++it;
    return r;
  } else {
    cerr << "*it = " << *it << endl;
    throw "parse error";
  }
}

bool eval_not(Iterator& it, const Iterator& last)
{
  if (*it == '!') {
    ++it;
    return !eval_not(it, last);
  } else {
    return eval_factor(it, last);
  }
}

bool eval_and(Iterator& it, const Iterator& last)
{
  bool r = eval_not(it, last);
  while (it != last && *it == '&') {
    ++it;
    const bool t = eval_not(it, last);
    r = r && t;
  }
  return r;
}

bool eval_or(Iterator& it, const Iterator& last)
{
  bool r = eval_and(it, last);
  while (it != last && *it == '|') {
    ++it;
    const bool t = eval_and(it, last);
    r = r || t;
  }
  return r;
}

int main()
{
  string s;
  int c = 0;
  char msg[] = "FV";
  while (getline(cin, s)) {
    string::const_iterator it = s.begin();
    const string::const_iterator end = remove(s.begin(), s.end(), ' ');
    cout << "Expression " << ++c << ": " << msg[eval_or(it, end)] << endl;
  }
  return 0;
}