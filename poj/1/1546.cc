#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <string>
using namespace std;

string to_s(int n, int base)
{
  if (n == 0) {
    return "0";
  }
  string ret;
  while (n > 0) {
    static const char tbl[] = "0123456789ABCDEF";
    ret = tbl[n % base] + ret;
    n /= base;
  }
  if (ret.size() > 7) {
    return "ERROR";
  } else {
    return ret;
  }
}

int main()
{
  string n;
  int from, to;
  while (cin >> n >> from >> to) {
    printf("%7s\n", to_s(strtol(n.c_str(), NULL, from), to).c_str());
  }
  return 0;
}