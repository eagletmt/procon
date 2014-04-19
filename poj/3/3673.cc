#include <iostream>
#include <string>
using namespace std;

int main(void)
{
  string a, b;
  cin >> a >> b;
  const int N = a.size(), M = b.size();
  int ret = 0;
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      ret += (a[i]-'0') * (b[j]-'0');
    }
  }
  cout << ret << endl;
  return 0;
}
