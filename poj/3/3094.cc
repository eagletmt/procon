#include <iostream>
#include <functional>
#include <numeric>
using namespace std;

struct quicksum : binary_function<int, char, int> {
  int pos;
  quicksum() : pos(0) {}
  int operator()(int acc, char c)
  {
    pos++;
    return acc + (c == ' ' ? 0 : pos * (c-'A'+1));
  }
};

int main(void)
{
  string s;
  while (getline(cin, s) && s != "#") {
    cout << accumulate(s.begin(), s.end(), 0, quicksum()) << endl;
  }
  return 0;
}
