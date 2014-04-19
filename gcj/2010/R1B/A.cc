#include <iostream>
#include <set>
#include <vector>
using namespace std;

int main()
{
  int T;
  cin >> T;
  for (int t = 1; t <= T; t++) {
    int N, M;
    cin >> N >> M;
    set<string> dirs;
    for (int i = 0; i < N; i++) {
      string s;
      cin >> s;
      for (int j = 1; j < s.size(); j++) {
        if (s[j] == '/') {
          dirs.insert(s.substr(0, j));
        }
      }
      dirs.insert(s);
    }

    int ans = 0;
    for (int i = 0; i < M; i++) {
      string s;
      cin >> s;
      for (int j = 1; j < s.size(); j++) {
        if (s[j] == '/') {
          if (dirs.insert(s.substr(0, j)).second) {
            ans++;
          }
        }
      }
      if (dirs.insert(s).second) {
        ans++;
      }
    }
    cout << "Case #" << t << ": " << ans << endl;
  }
  return 0;
}
