#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int to_i(char c)
{
  switch (c) {
    case 'A': return 1;
    case 'T': return 10;
    case 'J': return 11;
    case 'Q': return 12;
    case 'K': return 13;
    default: return c-'0';
  }
}

void to_ns(int ns[5], const string hand[5])
{
  for (int i = 0; i < 5; i++) {
    ns[i] = to_i(hand[i][0]);
  }
  sort(ns, ns+5);
}

int kihon(const string hand[5], const int points[4][13])
{
  int s = 0;
  for (int i = 0; i < 5; i++) {
    const int n = to_i(hand[i][0])-1;
    int c;
    switch (hand[i][1]) {
      case 'S': c = 0; break;
      case 'C': c = 1; break;
      case 'H': c = 2; break;
      case 'D': c = 3; break;
    }
    //cout << hand[i] << " = " << n << "," << c << endl;
    s += points[c][n];
  }
  return s;
}

bool fullhouse(const string hand[5])
{
  int ns[5];
  to_ns(ns, hand);
  return
    (ns[0] == ns[1] && ns[2] == ns[3] && ns[3] == ns[4])
    || (ns[0] == ns[1] && ns[1] == ns[2] && ns[3] == ns[4]);
}

bool flash(const string hand[5])
{
  const int c = hand[0][1];
  for (int i = 1; i < 5; i++) {
    if (hand[i][1] != c) {
      return false;
    }
  }
  return true;
}

bool straight(const string hand[5])
{
  int ns[5];
  to_ns(ns, hand);
  if (ns[0] == 1 && ns[1] == 10 && ns[2] == 11 && ns[3] == 12 && ns[4] == 13) {
    return true;
  } else {
    for (int i = 0; i < 4; i++) {
      if (ns[i+1]-1 != ns[i]) {
        return false;
      }
    }
    return true;
  }
}

bool royal(const string hand[5])
{
  if (!flash(hand)) {
    return false;
  } else if (!straight(hand)) {
    return false;
  } else {
    int ns[5];
    to_ns(ns, hand);
    return ns[0] == 1 && ns[1] == 10;
  }
}

bool cards(const string hand[5], int N)
{
  int ns[5];
  to_ns(ns, hand);
  for (int i = 0; i <= 5-N; i++) {
    for (int j = 0; j < N; j++) {
      if (ns[i] != ns[j+i]) {
        goto NEXT;
      }
    }
    return true;
NEXT:
    ;
  }
  return false;
}

bool twopair(const string hand[5])
{
  int ns[5];
  to_ns(ns, hand);
  return (ns[0] == ns[1] && (ns[2] == ns[3] || ns[3] == ns[4]))
    || (ns[1] == ns[2] && ns[3] == ns[4]);
}

int poker(const string hand[5], const int pats[9])
{
  if (royal(hand)) {
    return pats[8];
  } else if (straight(hand) && flash(hand)) {
    return pats[7];
  } else if (cards(hand, 4)) {
    return pats[6];
  } else if (fullhouse(hand)) {
    return pats[5];
  } else if (flash(hand)) {
    return pats[4];
  } else if (straight(hand)) {
    return pats[3];
  } else if (cards(hand, 3)) {
    return pats[2];
  } else if (twopair(hand)) {
    return pats[1];
  } else if (cards(hand, 2)) {
    return pats[0];
  } else {
    return 0;
  }
}

int main()
{
  int N;
  bool first = true;
  while (cin >> N) {
    int points[4][13];
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 13; j++) {
        cin >> points[i][j];
      }
    }
    int pats[9];
    for (int i = 0; i < 9; i++) {
      cin >> pats[i];
    }

    if (!first) {
      cout << endl;
    }
    first = false;

    for (int i = 0; i < N; i++) {
      string hand[5];
      for (int j = 0; j < 5; j++) {
        cin >> hand[j];
      }

      const int k = kihon(hand, points);
      const int p = poker(hand, pats);
      cout << k*p << endl;
    }
  }
  return 0;
}
