#include <iostream>
#include <vector>
using namespace std;

bool tag(const string& w)
{
  return w[0] == '<';
}

void render(const vector<string>& ws)
{
  int pos = 0;
  for (vector<string>::const_iterator it = ws.begin(); it != ws.end(); ++it) {
    if (tag(*it)) {
      if (*it == "<br>") {
        if (pos == 80) {
          cout << endl;
        }
        cout << endl;
        pos = 0;
      } else if (*it == "<hr>") {
        if (pos != 0) {
          cout << endl;
        }
        cout << "--------------------------------------------------------------------------------";
        pos = 80;
      }
    } else {
      // literal
      if (pos + it->size() >= 80) {
        cout << endl << *it;
        pos = it->size();
      } else {
        if (pos != 0) {
          cout << ' ';
          pos++;
        }
        cout << *it;
        pos += it->size();
      }
    }
  }
  cout << endl;
}


int main(void)
{
  string str;
  vector<string> ws;
  while (cin >> str) {
    ws.push_back(str);
  }
  render(ws);
  return 0;
}

