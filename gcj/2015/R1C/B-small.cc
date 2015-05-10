#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

int count_substring(const string& s, const string& sub)
{
  const int S = s.size();
  int c = 0;
  for (int i = 0; i < S; i++) {
    if (s.substr(i, sub.size()) == sub) {
      ++c;
    }
  }
  return c;
}

int max_case;

int solve2(const string& keyboard, const string& target, int S, const string& acc)
{
  if (S == 0) {
    const int c = count_substring(acc, target);
    max_case = max(max_case, c);
    return c;
  } else {
    const int K = keyboard.size();
    int c = 0;
    for (int i = 0; i < K; i++) {
      c += solve2(keyboard, target, S-1, acc + keyboard[i]);
    }
    return c;
  }
}

double solve(const string& keyboard, const string& target, int S)
{
  max_case = 0;
  const double e = (solve2(keyboard, target, S, "") / pow(double(keyboard.size()), double(S)));
  return max_case - e;
}

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int K, L, S;
    cin >> K >> L >> S;
    string keyboard, target;
    cin >> keyboard >> target;
    printf("Case #%d: %.8f\n", Ti, solve(keyboard, target, S));
  }
  return 0;
}
