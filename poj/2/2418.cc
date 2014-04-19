#include <iostream>
#include <cstdio>
#include <map>
using namespace std;

int main()
{
  map<string, int> m;
  int s = 0;
  for (string t; getline(cin, t); s++) {
    ++m[t];
  }
  for (map<string, int>::const_iterator it = m.begin(); it != m.end(); ++it) {
    printf("%s %.4f\n", it->first.c_str(), 100.0*it->second/s);
  }
  return 0;
}