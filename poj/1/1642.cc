#include <iostream>
#include <vector>
using namespace std;

int main()
{
  int N;
  while (cin >> N && N != 0) {
    vector<vector<vector<bool> > > blocks(N);
    int M, K;
    for (int i = 0; i < N; i++) {
      vector<int> row;
      for (int x; cin >> x && x != 0; ) {
        row.push_back(x);
      }
      if (i == 0) {
        M = row.size();
        K = row[0];
      }
      blocks[i].resize(M, vector<bool>(K, false));
      for (vector<int>::size_type j = 0; j < row.size(); j++) {
        for (int k = 0; k < row[j]; k++) {
          blocks[i][j][k] = true;
        }
      }
    }

    for (int k = 0; k < K; k++) {
      for (int i = 0; i < N; i++) {
        int j;
        for (j = 0; j < M && blocks[i][j][k]; j++);
        if (j == 0) {
          break;
        }
        if (i != 0) {
          cout << ' ';
        }
        cout << j;
      }
      cout << endl;
    }
    cout << endl;
    for (int j = 0; j < M; j++) {
      for (int k = 0; k < K; k++) {
        int i;
        for (i = 0; i < N && blocks[i][j][k]; i++);
        if (i == 0) {
          break;
        }
        if (k != 0) {
          cout << ' ';
        }
        cout << i;
      }
      cout << endl;
    }
    cout << "\n" << endl;
  }
  return 0;
}