#include <iostream>
#include <vector>
using namespace std;

int main(void)
{
  string encrypted, original;
  cin >> encrypted >> original;

  vector<int> a(26, 0), b(26, 0);
  for (int i = 0; i < original.size(); i++) {
    a[encrypted[i]-'A']++;
    b[original[i]-'A']++;
  }

  for (int i = 0; i < 26; i++) {
    if (a[i] != 0) {
      int j = 0;
      for (; j < 26; j++) {
        if (a[i] == b[j]) {
          b[j] = -1;
          break;
        }
      }
      if (j == 26) {
        cout << "NO" << endl;
        return 0;
      }
    }
  }
  cout << "YES" << endl;
  return 0;
}
