#include <iostream>
#include <stack>
using namespace std;

int main(void)
{
  string cmd;
  stack<string> back;
  stack<string> forward;
  back.push("http://www.acm.org/");

  while (cin >> cmd && cmd != "QUIT") {
    if (cmd == "VISIT") {
      string uri;
      cin >> uri;
      back.push(uri);
      forward = stack<string>();
      cout << uri << endl;
    } else if (cmd == "BACK") {
      if (back.size() == 1) {
        cout << "Ignored" << endl;
      } else {
        forward.push(back.top());
        back.pop();
        cout << back.top() << endl;
      }
    } else if (cmd == "FORWARD") {
      if (forward.empty()) {
        cout << "Ignored" << endl;
      } else {
        cout << forward.top() << endl;
        back.push(forward.top());
        forward.pop();
      }
    }
  }
  return 0;
}
