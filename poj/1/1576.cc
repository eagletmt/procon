#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int P, B, C;
  while (cin >> P >> B >> C && P != 0) {
    string board;
    cin >> board;
    board = "#" + board;
    vector<string> deck(C);
    for (int i = 0; i < C; i++) {
      cin >> deck[i];
    }

    vector<string::size_type> players(P, 0);
    int p = 0;
    int turn = 1;
    for (vector<string>::const_iterator it(deck.begin()); it != deck.end(); ++it, ++turn, p = (p+1) % P) {
      string::size_type i = board.find(it->at(0), players[p]);
      if (i == string::npos || i == board.size()-1) {
        cout << "Player " << (p+1) << " won after " << turn << " cards." << endl;
        goto NEXT;
      }
      players[p] = i+1;
      if (it->size() > 1) {
        i = board.find(it->at(1), players[p]);
        if (i == string::npos || i == board.size()-1) {
          cout << "Player " << (p+1) << " won after " << turn << " cards." << endl;
          goto NEXT;
        }
        players[p] = i+1;
      }
    }
    cout << "No player won after " << C << " cards." << endl;
NEXT:
    ;
  }
  return 0;
}