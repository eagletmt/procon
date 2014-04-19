#include <iostream>
#include <cstdio>
#include <vector>
#include <sstream>
using namespace std;

double eval(istringstream& iss)
{
  char c;
  iss >> c;
  if (c == '(') {
    double p;
    iss >> p;
    double e1 = eval(iss);
    double e2 = eval(iss);
    iss >> c;
    if (c != ')') {
      throw "parse error";
    }
    return e1 + (2*p - 1)*e2;
  } else {
    iss.putback(c);
    int n;
    iss >> n;
    return double(n);
  }
}

int main()
{
  string s;
  while (getline(cin, s) && s != "()") {
    istringstream iss(s);
    printf("%.2f\n", eval(iss));
  }
  return 0;
}