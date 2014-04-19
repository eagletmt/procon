#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int Ti = 1; Ti <= T; Ti++) {
    int M, C, W;
    cin >> M >> C >> W;
    --W;
    vector<int> cards(M);
    for (int i = 0; i < M; i++) {
      cards[i] = i+1;
    }
    vector<int> tmp;
    for (int i = 0; i < C; i++) {
      tmp.clear();
      int A, B;
      cin >> A >> B;
      --A;
      for (int j = A; j < A+B; j++) {
        tmp.push_back(cards[j]);
      }
      for (int j = 0; j < A; j++) {
        tmp.push_back(cards[j]);
      }
      for (int j = A+B; j < M; j++) {
        tmp.push_back(cards[j]);
      }
      swap(tmp, cards);
    }
    cout << "Case #" << Ti << ": " << cards[W] << endl;
  }
  return 0;
}
