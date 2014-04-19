#include <iostream>
#include <set>
#include <sstream>
using namespace std;

typedef enum { Club, Diamond, Spade, Heart } Color;

struct Card {
  int num;
  Color color;
  Card(char c, char n)
  {
    if (isdigit(n)) {
      num = n - '0';
    } else if (n == 'T') {
      num = 10;
    } else if (n == 'J') {
      num = 11;
    } else if (n == 'Q') {
      num =  12;
    } else if (n == 'K') {
      num = 13;
    } else if (n == 'A') {
      num = 14;
    }

    switch (c) {
      case 'C': color = Club; break;
      case 'D': color = Diamond; break;
      case 'S': color = Spade; break;
      case 'H': color = Heart; break;
    }
  }

  char show_color() const
  {
    static const char tbl[] = {'C', 'D', 'S', 'H'};
    return tbl[color];
  }

  char show_number() const
  {
    static const char tbl[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};
    return tbl[num-2];
  }

  bool operator<(const Card& c) const
  {
    return color == c.color ? num < c.num : color < c.color;
  }
};

int main()
{
  char c;
  while (cin >> c && c != '#') {
    int start;
    switch (c) {
      case 'N': start = 1;  break;
      case 'E': start = 2;  break;
      case 'S': start = 3;  break;
      case 'W': start = 0;  break;
    }

    set<Card> cards[4];
    for (int i = 0; i < 52; i++) {
      char a, b;
      cin >> a >> b;
      cards[(i+start)%4].insert(Card(a, b));
    }

    for (int i = 0; i < 4; i++) {
      const int index = (i+2) % 4;
      static const string player[] = {"North", "East", "South", "West"};
      cout << player[index] << " player:" << endl;
      cout << "+---+---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
      for (set<Card>::const_iterator it(cards[index].begin()); it != cards[index].end(); ++it) {
        cout << '|' << it->show_number() << ' ' << it->show_number();
      }
      cout << '|' << endl;
      for (set<Card>::const_iterator it(cards[index].begin()); it != cards[index].end(); ++it) {
        cout << "| " << it->show_color() << ' ';
      }
      cout << '|' << endl;
      for (set<Card>::const_iterator it(cards[index].begin()); it != cards[index].end(); ++it) {
        cout << '|' << it->show_number() << ' ' << it->show_number();
      }
      cout << '|' << endl;
      cout << "+---+---+---+---+---+---+---+---+---+---+---+---+---+" << endl;
    }
    cout << endl;
  }
  return 0;
}
