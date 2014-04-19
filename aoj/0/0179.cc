#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

static const char TBL[] = " rgb";

unsigned encode(const string& s)
{
  unsigned t = 0;
  for (string::const_iterator it = s.begin(); it != s.end(); ++it) {
    t <<= 2;
    switch (*it) {
      case 'r': t |= 1; break;
      case 'g': t |= 2; break;
      case 'b': t |= 3; break;
      default:  throw __LINE__;
    }
  }
  return t;
}

string decode(unsigned t)
{
  string s;
  while (t != 0) {
    s = TBL[t&3] + s;
    t >>= 2;
  }
  return s;
}

int bfs(unsigned init)
{
  queue<unsigned> q;
  vector<int> dist(1<<20, 10000000);
  q.push(init);
  dist[init] = 0;
  while (!q.empty()) {
    const int t = q.front();
    const string s = decode(t);
    q.pop();
    const int d = dist[t];
    const int N = s.size();
    if (count(s.begin(), s.end(), s[0]) == N) {
      return d;
    }
    for (int i = 0; i < N-1; i++) {
      if (s[i] != s[i+1]) {
        string u = s;
        for (int j = 1; j <= 3; j++) {
          if (TBL[j] != s[i] && TBL[j] != s[i+1]) {
            u[i] = u[i+1] = TBL[j];
            const unsigned v = encode(u);
            if (d+1 < dist[v]) {
              dist[v] = d+1;
              q.push(v);
            }
            break;
          }
        }
      }
    }
  }
  return -1;
}

int main()
{
  string s;
  while (cin >> s && s != "0") {
    const int ans = bfs(encode(s));
    if (ans < 0) {
      cout << "NA" << endl;
    } else {
      cout << ans << endl;
    }
  }
  return 0;
}
