#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <iterator>
#include <cctype>
using namespace std;

void proceed(vector<string>& grid, map<char, vector<pair<int,int> > >& snakes)
{
  const int N = grid.size();

  for (map<char, vector<pair<int,int> > >::iterator it(snakes.begin()); it != snakes.end(); ++it) {
    vector<pair<int,int> >& snake = it->second;
    const int di = snake[0].first - snake[1].first;
    const int dj = snake[0].second - snake[1].second;
    int i = snake[0].first + di;
    int j = snake[0].second + dj;
    if (i < 0 || N <= i || j < 0 || N <= j || grid[i][j] != '.') {
      // obstacles found. turn right
      if (di != 0) {
        i = snake[0].first;
        j = snake[0].second - di;
      } else {
        j = snake[0].second;
        i = snake[0].first + dj;
      }

      if (i < 0 || N <= i || j < 0 || N <= j || grid[i][j] != '.') {
        // obstacles found. turn left
        if (di != 0) {
          j = snake[0].second + di;
        } else {
          i = snake[0].first - dj;
        }
      }
    }

    if (0 <= i && i < N && 0 <= j && j < N && grid[i][j] == '.') {
      // move
      grid[i][j] = it->first;
      grid[snake.front().first][snake.front().second] = tolower(it->first);
      grid[snake.back().first][snake.back().second] = '.';
      for (vector<pair<int,int> >::size_type k = snake.size()-1; k > 0; k--) {
        snake[k] = snake[k-1];
      }
      snake[0].first = i;
      snake[0].second = j;
    }
  }
}

int main()
{
  int N, T;
  while (cin >> N >> T) {
    vector<string> grid(N);
    for (int i = 0; i < N; i++) {
      cin >> grid[i];
    }

    map<char, vector<pair<int,int> > > snakes;
    vector<vector<bool> > visited(N, vector<bool>(N, false));
    for (int i = 0; i < N; i++) {
      for (int j = 0; j < N; j++) {
        if (isupper(grid[i][j])) {
          vector<pair<int,int> > snake;
          const char c = tolower(grid[i][j]);
          queue<pair<int,int> > q;
          q.push(make_pair(i, j));
          while (!q.empty()) {
            const pair<int,int> p = q.front();
            q.pop();
            snake.push_back(p);
            for (int d = 0; d < 4; d++) {
              static const int di[] = {-1, 1, 0, 0}, dj[] = {0, 0, -1, 1};
              const int k = p.first + di[d], l = p.second + dj[d];
              if (0 <= k && k < N && 0 <= l && l < N && grid[k][l] == c && !visited[k][l]) {
                visited[k][l] = true;
                q.push(make_pair(k, l));
              }
            }
          }
          snakes.insert(make_pair(grid[i][j], snake));
        }
      }
    }

    for (int i = 0; i < T; i++) {
      proceed(grid, snakes);
    }
    copy(grid.begin(), grid.end(), ostream_iterator<string>(cout, "\n"));
  }
  return 0;
}
