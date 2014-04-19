#include <iostream>
#include <vector>
#include <queue>
using namespace std;

int main()
{
  int N;
  cin >> N;
  priority_queue<long long, vector<long long>, greater<long long> > q;
  for (int i = 0; i < N; i++) {
    long long l;
    cin >> l;
    q.push(l);
  }

  long long ans = 0;
  for (int i = 0; i < N-1; i++) {
    const long long x = q.top();  q.pop();
    const long long y = q.top();  q.pop();
    ans += x+y;
    q.push(x+y);
  }
  cout << ans << endl;
  return 0;
}