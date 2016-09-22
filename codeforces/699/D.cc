#include <iostream>
#include <vector>
using namespace std;

void dfs(vector<int> &g, int n, vector<int> &visited) {
  if (visited[g[n]] == 0) {
    visited[g[n]] = 1;
    dfs(g, g[n], visited);
    visited[g[n]] = 2;
  } else if (visited[g[n]] == 1) {
    g[n] = n;
  }
}

int main() {
  int N;
  cin >> N;
  vector<int> as(N);
  for (int i = 0; i < N; i++) {
    cin >> as[i];
    --as[i];
  }
  vector<int> g(as);

  vector<int> visited(N, 0);
  for (int i = 0; i < N; i++) {
    if (!visited[i]) {
      visited[i] = 1;
      dfs(g, i, visited);
      visited[i] = 2;
    }
  }

  int root = -1;
  for (int i = 0; i < N; i++) {
    if (as[i] == i) {
      root = i;
      break;
    }
  }
  for (int i = 0; i < N; i++) {
    if (g[i] == i) {
      if (root == -1) {
        root = i;
      } else {
        g[i] = root;
      }
    }
  }

  int ans = 0;
  for (int i = 0; i < N; i++) {
    if (as[i] != g[i]) {
      ++ans;
    }
  }
  cout << ans << endl;
  for (int i = 0; i < N; i++) {
    if (i != 0) {
      cout << ' ';
    }
    cout << g[i] + 1;
  }
  cout << endl;

  return 0;
}
