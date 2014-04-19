#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  using namespace std;
  int n;
  cin >> n;
  int s;
  cin >> s;
  vector<int> ls(n);
  for (int i = 0; i < n; i++) {
    cin >> ls[i];
  }
  sort(ls.begin(), ls.end());

  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i+1; j < n && ls[i] + ls[j] <= s; j++) {
      ++count;
    }
  }
  cout << count << endl;

  return 0;
}

