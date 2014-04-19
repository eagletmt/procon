#include <iostream>
using namespace std;

int main()
{
  static const int M = 1000;
  static int reg[10];
  static int mem[1000];
  for (int i = 0; cin >> mem[i]; i++);
  int ptr = 0;
  int ans = 0;
  for (ptr = 0; mem[ptr] != 100; ptr = (ptr + 1) % M, ++ans) {
    const int i = mem[ptr]/100;
    const int x = (mem[ptr]%100)/10;
    const int y = mem[ptr]%10;
    switch (i) {
      case 2:
        reg[x] = y;
        break;
      case 3:
        reg[x] = (reg[x] + y) % M;
        break;
      case 4:
        reg[x] = (reg[x] * y) % M;
        break;
      case 5:
        reg[x] = reg[y];
        break;
      case 6:
        reg[x] = (reg[x] + reg[y]) % M;
        break;
      case 7:
        reg[x] = (reg[x] * reg[y]) % M;
        break;
      case 8:
        reg[x] = mem[reg[y]];
        break;
      case 9:
        mem[reg[y]] = reg[x];
        break;
      case 0:
        if (reg[y] != 0) {
          ptr = reg[x]-1;
        }
    }
  }
  cout << ans+1 << endl;
  return 0;
}