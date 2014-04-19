#include <iostream>
using namespace std;

int main(void)
{
  int N;
  cin >> N;

  string max_team;
  int max_solved = 0, max_penalty = 0;
  cin >> max_team;
  for (int i = 0; i < 4; i++) {
    int sub, min;
    cin >> sub >> min;
    if (min != 0) {
      max_penalty += sub*min;
      max_solved++;
    }
  }

  for (int i = 1; i < N; i++) {
    string team;
    int solved = 0, penalty = 0;
    cin >> team;
    for (int j = 0; j < 4; j++) {
      int sub, min;
      cin >> sub >> min;
      if (min != 0) {
        penalty += min + 20*(sub-1);
        solved++;
      }
    }
    if (solved > max_solved) {
      max_team = team;
      max_solved = solved;
      max_penalty = penalty;
    } else if (solved == max_solved && penalty < max_penalty) {
      max_team = team;
      max_penalty = penalty;
    }
  }

  cout << max_team << ' ' << max_solved << ' ' << max_penalty << endl;
  return 0;
}
