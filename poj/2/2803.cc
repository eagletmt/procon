#include <iostream>
using namespace std;

string expand_suffix(const string& str)
{
  const string::size_type n = str.size();
  if (n > 2 && str.substr(n-2) == "er") {
    return "one who " + str.substr(0, n-2) + "s";
  } else if (n > 3 && str.substr(n-3) == "ing") {
    return "to actively " + str.substr(0, n-3);
  } else if (n > 3 && str.substr(n-3) == "ize") {
    return "change into " + str.substr(0, n-3);
  } else if (n > 1 && str.substr(n-1) == "s") {
    return "multiple instances of " + str.substr(0, n-1);
  } else if (n > 4 && str.substr(n-4) == "tion") {
    return "the process of " + str.substr(0, n-4) + "ing";
  } else {
    return str;
  }
}

string expand(const string& str)
{
  if (str.substr(0, 4) == "anti") {
    return "against " + expand_suffix(str.substr(4));
  } else if (str.substr(0, 4) == "post") {
    return "after " + expand_suffix(str.substr(4));
  } else if (str.substr(0, 3) == "pre") {
    return "before " + expand_suffix(str.substr(3));
  } else if (str.substr(0, 2) == "re") {
    return expand_suffix(str.substr(2)) + " again";
  } else if (str.substr(0, 2) == "un") {
    return "not " + expand_suffix(str.substr(2));
  } else {
    return expand_suffix(str);
  }
}

int main()
{
  int N;
  cin >> N;
  while (N-- > 0) {
    string s;
    cin >> s;
    cout << expand(s) << endl;
  }
  return 0;
}