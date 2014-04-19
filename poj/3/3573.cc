#include <iostream>
#include <sstream>
#include <algorithm>
using namespace std;

struct lower {
  char operator()(const char& c) const
  {
    return ::tolower(c);
  }
};

struct upper {
  char operator()(const char& c) const
  {
    return ::toupper(c);
  }
};

int main()
{
  string dict[26][26][31];
  string word;
  char c;

  while (cin.get(c)) {
    if (isalnum(c)) {
      word += c;
    } else {
      istringstream iss(word);
      char a, b;
      int n;
      if (iss >> a >> n >> b) {
        string abbr = dict[tolower(a)-'a'][tolower(b)-'a'][n];
        if (abbr != "" && abbr != "/") {
          if (isupper(a) && isupper(b)) {
            transform(abbr.begin(), abbr.end(), abbr.begin(), upper());
          }
          cout << a << abbr << b;
        } else {
          cout << word;
        }
      } else {
        if (word.size() > 2) {
          const char a = tolower(*word.begin());
          const char b = tolower(*word.rbegin());
          const string::size_type n = word.size()-2;
          string& found = dict[a-'a'][b-'a'][n];

          string foo(a+found+b), bar;
          transform(foo.begin(), foo.end(), foo.begin(), lower());
          transform(word.begin(), word.end(), inserter(bar, bar.begin()), lower());
          if (found != "" && foo != bar) {
            // ambiguous
            found = "/";
          } else {
            string abbr;
            transform(word.begin()+1, word.end()-1, inserter(abbr, abbr.begin()), lower());
            found = abbr;
          }
        }
        cout << word;
      }
      word = "";
      cout << c;
    }
  }
  return 0;
}
