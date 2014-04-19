#include <iostream>
#include <sstream>
#include <cctype>
#include <deque>
#include <map>
#include <algorithm>
using namespace std;

struct yaml
{
  string str;
  map<string, yaml> obj;
  yaml(const string& s) : str(s) {}
  yaml(const map<string, yaml>& m) : obj(m) {}

  string query(deque<string>& q) const
  {
    if (q.empty()) {
      if (str.empty()) {
        return "object";
      } else {
        return "string \"" + str + "\"";
      }
    } else {
      if (str.empty()) {
        map<string, yaml>::const_iterator it = obj.find(q.front());
        if (it == obj.end()) {
          return "no such property";
        } else {
          q.pop_front();
          return it->second.query(q);
        }
      } else {
        return "no such property";
      }
    }
  }
};

typedef string::const_iterator Iterator;

int indent(Iterator& it, const Iterator& last)
{
  int n = 0;
  while (it != last && *it == ' ') {
    ++n;
    ++it;
  }
  return n;
}

string key(Iterator& it, const Iterator& last)
{
  string s;
  while (it != last && (islower(*it) || isdigit(*it))) {
    s += *it;
    ++it;
  }
  return s;
}

string string_(Iterator& it, const Iterator& last)
{
  string s;
  while (it != last && (islower(*it) || isdigit(*it) || *it == ' ')) {
    s += *it;
    ++it;
  }
  return s;
}

yaml mapping(Iterator& it, const Iterator& last);

pair<string, yaml> mapping_item(Iterator& it, const Iterator& last)
{
  string k = key(it, last);
  if (*it != ':') {
    throw __LINE__;
  }
  ++it;
  if (*it == ' ') {
    ++it;
    string s = string_(it, last);
    if (*it != '\n') {
      throw __LINE__;
    }
    ++it;
    return make_pair(k, yaml(s));
  } else if (*it == '\n') {
    ++it;
    const yaml y = mapping(it, last);
    return make_pair(k, y);
  } else {
    throw __LINE__;
  }
}

yaml mapping(Iterator& it, const Iterator& last)
{
  map<string, yaml> obj;
  const int n = indent(it, last);
  obj.insert(mapping_item(it, last));
  while (it != last) {
    const Iterator saved = it;
    if (n != indent(it, last)) {
      it = saved;
      break;
    }
    obj.insert(mapping_item(it, last));
  }
  return yaml(obj);
}

int main()
{
  string q;
  getline(cin, q);
  deque<string> v;
  replace(q.begin(), q.end(), '.', ' ');
  for (istringstream iss(q); iss >> q;) {
    v.push_back(q);
  }

  string src;
  for (string s; getline(cin, s);) {
    src += s + "\n";
  }

  Iterator it = src.begin(), last = src.end();
  try {
    yaml y = mapping(it, last);
    cout << y.query(v) << endl;
  } catch (int n) {
    cerr << "Error at " << n << endl;
  }
  return 0;
}
