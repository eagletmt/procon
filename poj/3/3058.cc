#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void decode(char *dst, const char *src, int len)
{
  vector<pair<char,int> > with_index(len);
  for (int i = 0; i < len; i++) {
    with_index[i] = make_pair(src[i], i);
  }
  sort(with_index.begin(), with_index.end());
  vector<int> idx(len);
  for (int i = 0; i < len; i++) {
    idx[with_index[i].second] = i;
  }

  dst[len-1] = '.';
  for (int i = 0, cur = 0; i < len-1; i++, cur = idx[cur]) {
    dst[len-i-2] = src[cur];
  }
  dst[len] = '\0';
}

int expand(char *dst, const string& s)
{
  int len = 0;
  int t = 0;
  for (int i = 0; i < s.size(); i++) {
    if (isdigit(s[i])) {
      t = 10*t + s[i]-'0';
    } else {
      if (t != 0) {
        const char c = dst[len-1];
        for (int i = 0; i < t-1; i++) {
          dst[len] = c;
          len++;
        }
      }

      t = 0;
      dst[len] = s[i];
      len++;
      dst[len] = 0;
    }
  }
  
  if (t != 0) {
    const char c = dst[len-1];
    for (int i = 0; i < t-1; i++) {
      dst[len] = c;
      len++;
    }
  }
  dst[len] = '\0';
  return len;
}

int main()
{
  int N;
  cin >> N;
  char expanded[1000001], decoded[1000001];
  for (int i = 0; i < N; i++) {
    string s;
    cin >> s;
    const int len = expand(expanded, s);
    decode(decoded, expanded, len);
    cout << decoded << endl;
  }
  return 0;
}
