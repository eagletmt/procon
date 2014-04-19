#include <iostream>
#include <vector>
#include <queue>
#include <complex>
#include <map>
using namespace std;
typedef complex<int> P;

vector<vector<int> > convert(const vector<string>& grid)
{
  const int h = grid.size(), w = grid[0].size();
  vector<vector<int> > ret(h, vector<int>(w, 0));

  int id = 1;
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (grid[i][j] != '.' && ret[i][j] == 0) {
        queue<P> q;
        q.push(P(i, j));
        const char n = grid[i][j];
        ret[i][j] = id;
        while (!q.empty()) {
          const P p = q.front();
          q.pop();
          for (int d = 0; d < 4; d++) {
            static const P dir[] = {P(-1, 0), P(1, 0), P(0, -1), P(0, 1)};
            const P next = p + dir[d];
            if (0 <= next.real() && next.real() < h && 0 <= next.imag() && next.imag() < w
                && grid[next.real()][next.imag()] == n && ret[next.real()][next.imag()] == 0) {
              q.push(next);
              ret[next.real()][next.imag()] = id;
            }
          }
        }
        id++;
      }
    }
  }
  return ret;
}

pair<bool,pair<double,int> > check(vector<vector<int> >& grid, const P& start, int left, int right)
{
  const int h = grid.size(), w = grid[0].size();

  vector<P> points;
  queue<P> q;
  q.push(start);
  points.push_back(start);
  const int id = grid[start.real()][start.imag()];
  grid[start.real()][start.imag()] = 0;
  double m = start.imag()+0.5;
  while (!q.empty()) {
    const P p = q.front();
    q.pop();
    for (int d = 0; d < 4; d++) {
      static const P dir[] = {P(-1, 0), P(1, 0), P(0, -1), P(0, 1)};
      const P next = p + dir[d];
      if (0 <= next.real() && next.real() < h && 0 <= next.imag() && next.imag() < w
          && grid[next.real()][next.imag()] == id) {
        m += double(next.imag()) + 0.5;
        q.push(next);
        points.push_back(next);
        grid[next.real()][next.imag()] = 0;
      }
    }
  }

  map<int, pair<P, pair<int,int> > > children;
  for (int i = 0; i < 4; i++) {
    const int x = points[i].real(), y = points[i].imag();
    if (x > 0 && grid[x-1][y] != 0) {
      map<int, pair<P,pair<int,int> > >::iterator it = children.find(grid[x-1][y]);
      if (it == children.end()) {
        children.insert(make_pair(grid[x-1][y], make_pair(P(x-1, y), make_pair(y, y+1))));
      } else {
        it->second.second.first = min(it->second.second.first, y);
        it->second.second.second = max(it->second.second.second, y+1);
      }
    }
  }

  int cnt = 4;
  for (map<int,pair<P,pair<int,int> > >::const_iterator it(children.begin()); it != children.end(); ++it) {
    pair<bool, pair<double,int> > r = check(grid, it->second.first, it->second.second.first, it->second.second.second);
    if (!r.first) {
      return make_pair(false, make_pair(m, cnt));
    } else {
      m += r.second.first;
      cnt += r.second.second;
    }
  }
  const double g = m / cnt;
  return make_pair(left < g && g < right, make_pair(m, cnt));
}

int main()
{
  int w, h;
  while (cin >> w >> h && !(w == 0 && h == 0)) {
    vector<string> grid(h);
    for (int i = 0; i < h; i++) {
      cin >> grid[i];
    }

    P start;
    int left = w, right = 0;
    for (int j = 0; j < w; j++) {
      if (grid.back()[j] != '.') {
        start = P(h-1, j);
        left = min(left, j);
        right = max(right, j+1);
      }
    }
    vector<vector<int> > g = convert(grid);

    if (check(g, start, left, right).first) {
      cout << "STABLE" << endl;
    } else {
      cout << "UNSTABLE" << endl;
    }
  }
  return 0;
}
