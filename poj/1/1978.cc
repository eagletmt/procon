#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int n, r;
  while (cin >> n >> r && n != 0) {
    vector<int> cards(n);
    for (int i = 0; i < n; i++) {
      cards[i] = n-i;
    }
    for (int i = 0; i < r; i++) {
      int p, c;
      cin >> p >> c;
      --p;
      vector<int> t(cards.begin()+p, cards.begin()+p+c);
      for (int j = p-1; j >= 0; j--) {
        cards[j+c] = cards[j];
      }
      for (int j = 0; j < c; j++) {
        cards[j] = t[j];
      }
    }
    cout << cards.front() << endl;
  }
  return 0;
}