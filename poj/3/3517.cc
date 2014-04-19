#include <cstdio>
using namespace std;

int josephus(int n, int k, int s)
{
  long long x = static_cast<long long>(k)*s;
  while (x > n) {
    x = ((x-n)*k-1)/(k-1) ;
  }
  return x;
}

int main()
{
  int N, K, M;
  while (scanf("%d %d %d", &N, &K, &M) != EOF && N != 0) {
    const int ans = ((josephus(N, K, N) - K + M)%N + N)%N;
    printf("%d\n", ans == 0 ? N : ans);
  }
  return 0;
}