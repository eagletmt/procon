#include <iostream>
using namespace std;

struct vm
{
  unsigned char mem[32];

  static unsigned char inst(unsigned char c) { return c >> 5; }
  static unsigned char operand(unsigned char c) { return c & 0x1F; }

  unsigned char execute()
  {
    unsigned char acc = 0;
    unsigned char pc = 0;
    while (true) {
      const unsigned char i = inst(mem[pc]);
      const unsigned char o = operand(mem[pc]);
      pc = (pc+1) & 0x1F;
      switch (i) {
        case 0:
          mem[o] = acc;
          break;
        case 1:
          acc = mem[o];
          break;
        case 2:
          if (acc == 0) { pc = o; }
          break;
        case 3:
          break;
        case 4:
          --acc;
          break;
        case 5:
          ++acc;
          break;
        case 6:
          pc = o;
          break;
        case 7:
          return acc;
      }
    }
  }
};

static unsigned char read_bin(const string& bin)
{
  unsigned char a = 0;
  for (string::const_iterator it(bin.begin()); it != bin.end(); ++it) {
    a = 2*a + (*it - '0');
  }
  return a;
}

static string show_bin(unsigned char c)
{
  string s(8, '0');
  for (int i = 0; i < 8; i++, c >>= 1) {
    s[7-i] = (c & 1) + '0';
  }
  return s;
}

int main()
{
  string line;
  while (cin >> line) {
    vm m;
    m.mem[0] = read_bin(line);
    for (int i = 1; i < 32; i++) {
      cin >> line;
      m.mem[i] = read_bin(line);
    }

    cout << show_bin(m.execute()) << endl;
  }
  return 0;
}