#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct Error {};

struct manager
{
  int capacity, used;
  int uniq;
  typedef int ref_type;
  ref_type env[26];
  map<ref_type,int> ref;
  typedef string::const_iterator Iterator;

  manager(int M) : capacity(M), used(0), uniq(1)
  {
    ref.insert(make_pair(0, 0));
    fill_n(env, 26, -1);
  }

  void exec(const string& s)
  {
    Iterator it = s.begin(), last = s.end();
    line(it, last);
  }

  void line(Iterator& it, const Iterator& last)
  {
    if (*it == 'f') {
      free(it, last);
    } else {
      expr(it, last);
    }
  }

  ref_type expr(Iterator& it, const Iterator& last)
  {
    if (*it == '(') {
      ++it;
      ref_type r = expr(it, last);
      ++it;
      return r;
    } else if (*it == 'N' && it+1 != last && *(it+1) == 'U') {
      it += 4;  // NULL
      return 0;
    } else if (*it == 'm') {
      return malloc(it, last);
    } else if (*it == 'c') {
      return clone(it, last);
    } else {
      const char var = *it;
      ++it;
      if (it != last && *it == '=') {
        // assign
        ++it;
        const ref_type r = expr(it, last);
        env[var-'A'] = r;
        return r;
      } else {
        // variable
        return env[var-'A'];
      }
    }
  }

  ref_type malloc(Iterator& it, const Iterator& last)
  {
    it += 7;  // malloc(
    const int n = number(it, last);
    ++it;
    return malloc_(n);
  }

  ref_type clone(Iterator& it, const Iterator& last)
  {
    it += 6;  // clone(
    const ref_type r = expr(it, last);
    ++it;
    if (r == -1) {
      throw Error();
    } else if (r == 0) {
      return 0;
    } else {
      map<ref_type,int>::const_iterator jt = ref.find(r);
      if (jt == ref.end()) {
        throw Error();
      }
      return malloc_(jt->second);
    }
  }

  ref_type malloc_(int n)
  {
    if (used + n <= capacity) {
      used += n;
      const ref_type r = uniq;
      ++uniq;
      ref.insert(make_pair(r, n));
      return r;
    } else {
      return 0;
    }
  }

  void free(Iterator& it, const Iterator& last)
  {
    it += 5;  // free(
    const ref_type r = expr(it, last);
    ++it;
    if (r == -1) {
      throw Error();
    } else if (r == 0) {
      // do nothing
    } else {
      map<int,int>::iterator jt = ref.find(r);
      if (jt == ref.end()) {
        throw Error();
      }
      used -= jt->second;
      ref.erase(jt);
    }
  }

  int number(Iterator& it, const Iterator& last)
  {
    int n = 0;
    while (it != last && '0' <= *it && *it <= '9') {
      n = 10*n + (*it - '0');
      ++it;
    }
    return n;
  }

  int reachable() const
  {
    vector<ref_type> refs;
    for (int i = 0; i < 26; i++) {
      if (env[i] != -1) {
        refs.push_back(env[i]);
      }
    }
    sort(refs.begin(), refs.end());
    vector<ref_type>::const_iterator last = unique(refs.begin(), refs.end());
    int n = 0;
    for (vector<ref_type>::const_iterator it = refs.begin(); it != last; ++it) {
      map<ref_type, int>::const_iterator jt = ref.find(*it);
      if (jt != ref.end()) {
        n += jt->second;
      }
    }
    return n;
  }
};

int main()
{
  int M;
  cin >> M;
  cin.ignore();
  manager m(M);
  try {
    string line;
    while (getline(cin, line)) {
      m.exec(line);
    }
    cout << m.used - m.reachable() << endl;
  } catch (const Error&) {
    cout << "Error" << endl;
  }
  return 0;
}
