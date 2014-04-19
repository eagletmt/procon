#include <iostream>
#include <list>
#include <iterator>
using namespace std;

list<list<int> > comb(list<int>::iterator first, list<int>::iterator last, int n)
{
  if (n == 0) {
    list<int> l;
    list<list<int> > r;
    r.push_back(l);
    return r;
  } else {
    list<list<int> > ret;
    for (; first != last; ++first) {
      ++first;
      list<list<int> > xss = comb(first, last, n-1);
      --first;
      for (list<list<int> >::iterator it(xss.begin()); it != xss.end(); ++it) {
        it->push_front(*first);
        ret.push_back(*it);
      }
    }
    return ret;
  }
}

int main(void)
{
  int n;
  bool f = true;
  while (cin >> n && n != 0) {
    list<int> l;
    for (int i = 0; i < n; i++) {
      int x;
      cin >> x;
      l.push_back(x);
    }

    if (!f) {
      cout << endl;
    }
    f = false;

    list<list<int> > xss = comb(l.begin(), l.end(), 6);
    for (list<list<int> >::const_iterator it(xss.begin()); it != xss.end(); ++it) {
      list<int>::const_iterator jt(it->begin());
      cout << *jt;
      for (++jt; jt != it->end(); ++jt) {
        cout << ' ' << *jt;
      }
      cout << endl;
    }
  }

  return 0;
}
