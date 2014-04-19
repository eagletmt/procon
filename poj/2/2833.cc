#include <cstdio>
#include <queue>
using namespace std;

int main()
{
  int n, n1, n2;
  while (scanf("%d %d %d", &n1, &n2, &n) != EOF && !(n == 0 && n1 == 0 && n2 == 0)) {
    priority_queue<int> q1, q2;
    double sum = 0;
    for (int i = 0; i < n; i++) {
      int a;
      scanf("%d", &a);
      sum += a;
      q1.push(-a);
      if (q1.size() > n1) {
        q1.pop();
      }
      q2.push(a);
      if (q2.size() > n2) {
        q2.pop();
      }
    }

    for (int i = 0; i < n1; i++) {
      sum += q1.top();
      q1.pop();
    }
    for (int i = 0; i < n2; i++) {
      sum -= q2.top();
      q2.pop();
    }
    printf("%.6f\n", sum / (n-n2-n1));
  }
  return 0;
}
