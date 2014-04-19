#include <iostream>
#include <map>
using namespace std;

int main()
{
  int L, N;
  cin >> L >> N;
  map<string,string> irregular;
  for (int i = 0; i < L; i++) {
    string k, v;
    cin >> k >> v;
    irregular.insert(make_pair(k, v));
  }

  for (int i = 0; i < N; i++) {
    string word;
    cin >> word;
    const string::size_type len = word.size();
    map<string,string>::const_iterator it = irregular.find(word);
    if (it != irregular.end()) {
      cout << it->second << endl;
    } else if (word[len-1] == 'y' && word[len-2] != 'a' && word[len-2] != 'e' && word[len-2] != 'i'
        && word[len-2] != 'o' && word[len-2] != 'u') {
      word[len-1] = 'i';
      cout << word << "es" << endl;
    } else if (word[len-1] == 'o' || word[len-1] == 's' || word[len-1] == 'x'
        || word.substr(len-2) == "ch" || word.substr(len-2) == "sh") {
      cout << word << "es" << endl;
    } else {
      cout << word << 's' << endl;
    }
  }
  return 0;
}
