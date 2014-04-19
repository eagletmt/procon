#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n;
  while (cin >> n && n != 0) {
    string s;
    cin >> s;
    int row = s.size() / n;
    vector<string> text(row, string(n, ' '));
    for (int i = 0; i < row; i++) {
      for (int j = 0; j < n; j++) {
        if (i % 2 == 0) {
          text[i][j] = s[i*n + j];
        } else {
          text[i][j] = s[(i+1)*n - j-1];
        }
      }
    }
    for (int j = 0; j < n; j++) {
      for (int i = 0; i < row; i++) {
        cout << text[i][j];
      }
    }
    cout << endl;
  }
  return 0;
}
