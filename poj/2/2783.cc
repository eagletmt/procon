#include <iostream>
#include <vector>
using namespace std;

void deposite(vector<int>& hooks, int& pos, int n)
{
  const int N = hooks.size();
  int start = -1;
  int f = 0;
  for (int i = 0; i < 2*N; i++) {
    const int j = (i + pos) % N;
    if (hooks[j] > 0) {
      f = 0;
      start = -1;
    } else {
      ++f;
      if (start == -1) {
        start = j;
      }
      if (f == n+2) {
        break;
      }
    }
  }
  if (f != n+2) {
    cout << "No space left, please come back later." << endl;
  } else {
    --hooks[start];
    for (int i = 1; i < n+1; i++) {
      ++hooks[(start + i) % N];
    }
    --hooks[(start+n+1)%N];
    pos = (start+n+1) % N;
    cout << "The launderer gives ticket " << start << "." << endl;
  }
}

void withdraw(vector<int>& hooks, int& pos, int k)
{
  const int N = hooks.size();
  cout << "The launderer gives back batch " << k << "." << endl;
  pos = k;
  ++hooks[k];
  if (hooks[k] == 0) {
    cout << k << " is freed." << endl;
  }
  int i = (k+1)%N;
  for (; hooks[i] > 0; i = (i+1)%N) {
    hooks[i] = 0;
    cout << i << " is freed." << endl;
  }
  ++hooks[i];
  if (hooks[i] == 0) {
    cout << i << " is freed." << endl;
  }
}

int main()
{
  int N;
  cin >> N;
  vector<int> hooks(N, 0);
  int L;
  cin >> L;
  int pos = 0;
  for (int i = 0; i < L; i++) {
    string cmd;
    cin >> cmd;
    if (cmd == "D") {
      int n;
      cin >> n;
      deposite(hooks, pos, n);
    } else if (cmd == "W") {
      int k;
      cin >> k;
      withdraw(hooks, pos, k);
    } else {
      while (true) {}
    }
  }
  return 0;
}