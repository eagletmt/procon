#include <iostream>
#include <sstream>
#include <queue>
using namespace std;

struct compare {
  bool operator()(const string& s, const string& t) const
  {
    const string::size_type len = min(s.size(), t.size());
    for (string::size_type i = 0; i < len; i++) {
      const char x = tolower(s[i]);
      const char y = tolower(t[i]);
      if (x != y) {
        return x > y;
      }
    }
    return s.size() > t.size();
  }
};

int main()
{
  string input;
  while (getline(cin, input) && input != ".") {
    for (string::iterator it(input.begin()); it != input.end();) {
      if (*it == ',' || *it == '.') {
        it = input.erase(it);
        if (it != input.end()) {
          ++it;
        }
      } else {
        ++it;
      }
    }

    priority_queue<int, vector<int>, greater<int> > nums;
    priority_queue<string, vector<string>, compare> words;
    vector<bool> is_num;

    stringstream iss(input);
    while (!iss.eof()) {
      int n;
      if (iss >> n) {
        is_num.push_back(true);
        nums.push(n);
      } else {
        iss.clear();
        is_num.push_back(false);
        string w;
        iss >> w;
        words.push(w);
      }
    }

    for (int i = 0; i < is_num.size(); i++) {
      if (i != 0) {
        cout << ", ";
      }
      if (is_num[i]) {
        cout << nums.top();
        nums.pop();
      } else {
        cout << words.top();
        words.pop();
      }
    }
    cout << '.' << endl;
  }
  return 0;
}
