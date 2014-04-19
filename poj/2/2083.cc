#include <iostream>
#include <vector>
#include <iterator>
using namespace std;

vector<string> fractal(int n)
{
  if (n == 1) {
    vector<string> v(1);
    v[0] = ("X");
    return v;
  } else if (n == 2) {
    vector<string> v(3);
    v[0] = v[2] = "X X";
    v[1] = " X ";
    return v;
  } else {
    vector<string> b = fractal(n-1);
    const int size = b.size();
    vector<string> v(3*size);

    for (int i = 0; i < size; i++) {
      v[i] = b[i];
      for (int j = 0; j < size; j++) {
        v[i] += ' ';
      }
      v[i] += b[i];
    }
    for (int i = 0; i < size; i++) {
      for (int j = 0; j < size; j++) {
        v[size+i] += ' ';
      }
      v[size+i] += b[i];
      for (int j = 2*size; j < 3*size; j++) {
        v[size+i] += ' ';
      }
    }
    for (int i = 0; i < size; i++) {
      v[2*size+i] = b[i];
      for (int j = 0; j < size; j++) {
        v[2*size+i] += ' ';
      }
      v[2*size+i] += b[i];
    }
    return v;
  }
}

void print(const vector<string>& v)
{
  copy(v.begin(), v.end(), ostream_iterator<string>(cout, "\n"));
}

int main(void)
{
  int n;
  while (cin >> n && n != -1) {
    print(fractal(n));
    cout << '-' << endl;
  }
  return 0;
}
