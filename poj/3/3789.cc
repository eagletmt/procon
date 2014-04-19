#include <iostream>
using namespace std;

int main()
{
  int N;
  cin >> N;
  for (int n = 1; n <= N; n++) {
    string s;
    cin >> s;
    int hms[3];
    hms[0] = 10*(s[0]-'0')+s[1]-'0';
    hms[1] = 10*(s[3]-'0')+s[4]-'0';
    hms[2] = 10*(s[6]-'0')+s[7]-'0';
    cout << n << ' ';
    for (int i = 5; i >= 0; i--) {
      for (int j = 0; j < 3; j++) {
        cout << ((hms[j]>>i)&1);
      }
    }
    cout << ' ';
    for (int j = 0; j < 3; j++) {
      for (int i = 5; i >= 0; i--) {
        cout << ((hms[j]>>i)&1);
      }
    }
    cout << endl;
  }
  return 0;
}
