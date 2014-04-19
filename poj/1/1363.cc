#include <iostream>
#include <vector>
#include <stack>
#include <iterator>
using namespace std;

bool solve(const vector<int>& v)
{
  const int N = v.size();
  stack<int> stk;
  vector<int>::const_iterator it(v.begin());
  for (int i = 1; i <= N; i++) {
    stk.push(i);
    while (!stk.empty() && *it == stk.top()) {
      ++it;
      stk.pop();
    }
  }
  return stk.empty();
}

int main(void)
{
  int N;
  bool b = false;
  while (cin >> N && N != 0) {
    if (b) {
      cout << endl;
    }
    b = true;
    int t;
    while (cin >> t && t != 0) {
      vector<int> input(N);
      input[0] = t;
      for (int i = 1; i < N; i++) {
        cin >> input[i];
      }
      cout << (solve(input) ? "Yes" : "No") << endl;
    }
  }

  return 0;
}
