#include <iostream>
#include <vector>
using namespace std;

int mod(int n, int k)
{
  return (n%k + k) % k;
}

bool tbl[10000][100];

int main(void)
{
  int N, K;
  cin >> N >> K;

  vector<int> seq(N);
  for (int i = 0; i < N; i++) {
    cin >> seq[i];
  }

  tbl[0][mod(seq[0], K)] = true;
  for (int i = 1; i < N; i++) {
    for (int j = 0; j < K; j++) {
      if (tbl[i-1][j]) {
        tbl[i][mod(j + seq[i], K)] = true;
        tbl[i][mod(j - seq[i], K)] = true;
      }
    }
  }

  if (tbl[N-1][0]) {
    cout << "Divisible" << endl;
  } else {
    cout << "Not divisible" << endl;
  }

  return 0;
}
