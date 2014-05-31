#include <iostream>
#include <map>
#include <queue>
#include <algorithm>
using namespace std;

bool goal_p(const vector<int>& v)
{
  const int N = v.size();
  int m = -1;
  for (int i = 0; i < N-1; i++) {
    if (m == -1) {
      if (v[i] > v[i+1]) {
        m = i;
      }
    } else {
      if (v[i] < v[i+1]) {
        return false;
      }
    }
  }
  return true;
}

int solve(const vector<int>& A)
{
  const int N = A.size();
  map<vector<int>, int> dist;
  dist[A] = 0;
  queue<vector<int> > q;
  q.push(A);
  while (!q.empty()) {
    vector<int> v = q.front();
    q.pop();
    const int d = dist[v];
    if (goal_p(v)) {
      return d;
    }

    for (int i = 0; i < N-1; i++) {
      swap(v[i], v[i+1]);
      if (!dist.count(v)) {
        dist.insert(make_pair(v, d+1));
        q.push(v);
      }
      swap(v[i], v[i+1]);
    }
  }
  throw __LINE__;
}

int main()
{
  int T;
  cin >> T;

  for (int Ti = 1; Ti <= T; Ti++) {
    cout << "Case #" << Ti << ": ";

    int N;
    cin >> N;
    vector<int> A(N);
    for (int i = 0; i < N; i++) {
      cin >> A[i];
    }
    cout << solve(A) << endl;
  }
  return 0;
}
