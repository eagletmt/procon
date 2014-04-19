#include <iostream>
using namespace std;

int main()
{
  int n;
  cin >> n;
  int count = 0;
  int sum = 0;
  for (int i = 0; sum <= n; i++) {
    sum += i;
    if ((n - sum) % (i+1) == 0 && n != sum) {
      count++;
    }
  }
  cout << count << endl;
  return 0;
}
