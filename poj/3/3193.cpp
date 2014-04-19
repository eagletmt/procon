#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
  int n, m;
  string nm;
  getline(cin, nm);
  istringstream iss(nm);
  iss >> m >> n;

  vector<string> phrasebook(m);
  for (int i = 0; i < m; i++) {
    getline(cin, phrasebook[i]);
  }
  sort(phrasebook.begin(), phrasebook.end());

  vector<string> input(n);
  for (int i = 0; i < n; i++) {
    getline(cin, input[i]);
  }
  sort(input.begin(), input.end());

  // search
  int i, j, count;
  i = j = count = 0;
  while (i < m && j < n) {
    string sub(phrasebook[i].substr(0, input[j].size()));
    if (sub < input[j]) {
      i++;
    } else if (sub > input[j]) {
      j++;
    } else {
      count++;
      j++;
    }
  }

  cout << count << endl;

  return 0;
}


