#include <iostream>
#include <sstream>
#include <vector>
#include <map>
using namespace std;
static const int INF = 100000000;

struct node
{
  int cost;
  vector<int> children;
  vector<int> dp;
};

int solve(vector<node>& tree, int M, int node = 0)
{
  int value = 1;
  for (vector<int>::const_iterator it(tree[node].children.begin()); it != tree[node].children.end(); ++it) {
    value += solve(tree, M, *it);
  }

  const int N = tree.size();
  vector<int>& dp = tree[node].dp;
  dp.resize(N+1, INF);
  dp[0] = 0;
  for (int i = 1; i <= value; i++) {
    dp[i] = tree[node].cost;
  }
  for (vector<int>::const_iterator it(tree[node].children.begin()); it != tree[node].children.end(); ++it) {
    const vector<int>& dp_child = tree[*it].dp;
    for (int i = value; i >= 0; i--) {
      for (int j = 1; j <= N; j++) {
        if (i-j >= 0) {
          dp[i] = min(dp[i], dp[i-j] + dp_child[j]);
        }
      }
    }
  }
  return value;
}

int main()
{
  string s;
  while (getline(cin, s) && s != "#") {
    int N, M;
    {
      istringstream iss(s);
      iss >> N >> M;
    }
    map<string,int> m;
    vector<node> tree(N+1);
    tree[0].cost = INF;
    vector<bool> owned(N+1, false);
    for (int i = 0; i < N; i++) {
      getline(cin, s);
      istringstream iss(s);
      string t;
      int c;
      iss >> t >> c;
      int id;
      map<string,int>::const_iterator it = m.find(t);
      if (it == m.end()) {
        id = m.size()+1;
        m.insert(make_pair(t, id));
      } else {
        id = it->second;
      }
      tree[id].cost = c;

      while (iss >> t) {
        it = m.find(t);
        int j;
        if (it == m.end()) {
          j = m.size()+1;
          m.insert(make_pair(t, j));
        } else {
          j = it->second;
        }
        tree[id].children.push_back(j);
        owned[j] = true;
      }
    }
    for (int i = 1; i <= N; i++) {
      if (!owned[i]) {
        tree[0].children.push_back(i);
      }
    }
    solve(tree, M);
    cout << tree[0].dp[M] << endl;
  }
  return 0;
}