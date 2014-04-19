#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  int P;
  cin >> P;
  vector<int> portions(P);
  for (int i = 0; i < P; i++) {
    cin >> portions[i];
  }

  vector<int> even(P), odd(P);
  odd[0] = portions[0];
  even[0] = 0;
  for (int i = 1; i < P; i++) {
    const int p = portions[i];
    even[i] = max(odd[i-1]-p, even[i-1]);
    odd[i] = max(odd[i-1], even[i-1]+p);
  }
  cout << max(even[P-1], odd[P-1]) << endl;

  return 0;
}
