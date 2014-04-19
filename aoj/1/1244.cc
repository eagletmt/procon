#include <iostream>
#include <string>
#include <map>
using namespace std;

struct unknown {};
struct parse_error {};

typedef string::const_iterator Iterator;

map<string,int> env;

int number(Iterator& it, const Iterator& last)
{
  if (!isdigit(*it)) {
    return 1;
  }
  int n = 0;
  while (it != last && isdigit(*it)) {
    n = 10*n + (*it - '0');
    ++it;
  }
  return n;
}

int atom(Iterator& it, const Iterator& last)
{
  if (!isupper(*it)) {
    throw parse_error();
  }
  string name = string(1, *it);
  ++it;
  while (it != last && islower(*it)) {
    name += *it;
    ++it;
  }
  map<string,int>::const_iterator jt = env.find(name);
  if (jt == env.end()) {
    throw unknown();
  } else {
    return jt->second;
  }
}

int molecule(Iterator& it, const Iterator& last)
{
  int ans = 0;
  while (it != last && (*it == '(' || isupper(*it))) {
    if (*it == '(') {
      ++it;
      int r = molecule(it, last);
      if (*it != ')') {
        throw parse_error();
      }
      ++it;
      int n = number(it, last);
      ans += n*r;
    } else {
      int r = atom(it, last);
      if (it != last) {
        int n = number(it, last);
        ans += n*r;
      } else {
        ans += r;
      }
    }
  }
  return ans;
}

int main()
{
  string line;
  while (cin >> line && line != "END_OF_FIRST_PART") {
    int n;
    cin >> n;
    env.insert(make_pair(line, n));
  }

  while (cin >> line && line != "0") {
    try {
      Iterator it = line.begin(), last = line.end();
      cout << molecule(it, last) << endl;
    } catch (const unknown&) {
      cout << "UNKNOWN" << endl;
    }
  }
  return 0;
}
