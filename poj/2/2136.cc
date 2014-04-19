#include <iostream>
#include <vector>
#include <cctype>
#include <iterator>
using namespace std;

int main()
{
  vector<int> hist(26, 0);
  char c;
  int m = 0;
  while (cin >> c) {
    if (isalpha(c)) {
      hist[c-'A']++;
      m = max(m, hist[c-'A']);
    }
  }
  vector<string> graph(m+1, "A B C D E F G H I J K L M N O P Q R S T U V W X Y Z");
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < 26; j++) {
      graph[i][2*j] = hist[j] >= m-i ? '*' : ' ';
    }
    string::size_type p = graph[i].find_last_of('*');
    graph[i] = graph[i].substr(0, p+1);
  }
  copy(graph.begin(), graph.end(), ostream_iterator<string>(cout, "\n"));
  return 0;
}
