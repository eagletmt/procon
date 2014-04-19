#include <iostream>
using namespace std;

int main()
{
  int N;
  cin >> N;
  static int v[100010];
  for (int i = 0; i < N; i++) {
    int a, b;
    cin >> a >> b;
    ++v[a];
    --v[b+1];
  }
  int ans = 0;
  int acc = 0;
  for (int i = 0; i <= N+1; i++) {
    acc += v[i];
    if (acc >= i-1) {
      ans = i-1;
    }
  }
  cout << ans << endl;
  return 0;
}
