#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

struct too_long {};

vector<string> expand(const vector<string>& v, const map<string, vector<string> >& syntax)
{
  static const string::size_type MAXLEN = 200;
  vector<string> ans;
  for (vector<string>::const_iterator it = v.begin(); it != v.end(); ++it) {
    if ((*it)[0] == '[') {
      // terminal
      ans.push_back(it->substr(1, it->size()-2));
    } else {
      // non-terminal
      const vector<string> w = expand(syntax.find(*it)->second, syntax);
      for (vector<string>::const_iterator jt = w.begin(); jt != w.end(); ++jt) {
        ans.push_back(*jt);
      }
    }
    if (ans.size() > MAXLEN) {
      throw too_long();
    }
  }
  return ans;
}

int solve(const vector<string>& tokens, int A, int T, int G, int C)
{
  static int dp[201][51][51][51];
  dp[0][0][0][0] = 1;
  const int L = A+T+G+C;
  static const int M = 1000000007;

  for (int i = 0; i < L; i++) {
    const string& token = tokens[i];
    const bool has_a = token.find('A') != string::npos;
    const bool has_t = token.find('T') != string::npos;
    const bool has_g = token.find('G') != string::npos;
    const bool has_c = token.find('C') != string::npos;
    for (int a = 0; a <= A; a++) {
      for (int t = 0; t <= T; t++) {
        for (int g = 0; g <= G; g++) {
          const int c = i - a - t - g;
          if (c < 0) {
            continue;
          }
          const int cur = dp[i][a][t][g];
          if (has_a && a+1 <= A) {
            dp[i+1][a+1][t][g] = (dp[i+1][a+1][t][g] + cur) % M;
          }
          if (has_t && t+1 <= T) {
            dp[i+1][a][t+1][g] = (dp[i+1][a][t+1][g] + cur) % M;
          }
          if (has_g && g+1 <= G) {
            dp[i+1][a][t][g+1] = (dp[i+1][a][t][g+1] + cur) % M;
          }
          if (has_c && c+1 <= C) {
            dp[i+1][a][t][g] = (dp[i+1][a][t][g] + cur) % M;
          }
        }
      }
    }
  }
  return dp[L][A][T][G];
}

int main()
{
  int a, t, g, c;
  cin >> a >> t >> g >> c;
  int M;
  cin >> M;
  cin.ignore();
  map<string, vector<string> > syntax;
  vector<string> top;
  for (int i = 0; i < M; i++) {
    string s;
    getline(cin, s);
    replace(s.begin(), s.end(), ':', ' ');
    istringstream iss(s);
    string k;
    iss >> k;
    vector<string> v;
    for (string x; iss >> x;) {
      v.push_back(x);
    }
    if (i == 0) {
      top = v;
    }
    syntax.insert(make_pair(k, v));
  }

  try {
    vector<string> tokens = expand(top, syntax);
    if (tokens.size() != a+g+c+t) {
      cout << 0 << endl;
    } else {
      cout << solve(tokens, a, t, g, c) << endl;
    }
  } catch (const too_long&) {
    cout << 0 << endl;
  }
  return 0;
}
