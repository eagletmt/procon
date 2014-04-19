#include <cstdio>
using namespace std;

static unsigned turn(unsigned s, int n)
{
  const int r = n/4;
  const int c = n%4;
  for (int i = 0; i < 4; i++) {
    s = (s ^ (1 << (4*r+i)));
  }
  for (int j = 0; j < 4; j++) {
    s = (s ^ (1 << (4*j+c)));
  }
  return s ^ (1 << n);
}

int main()
{
  unsigned goal = 0;
  for (int i = 0; i < 4; i++) {
    char line[5];
    scanf("%s", line);
    for (int j = 0; j < 4; j++) {
      goal |= ((line[j] == '+' ? 1 : 0) << (i*4+j));
    }
  }

  for (unsigned s = 0; s < (1<<16); ++s) {
    unsigned b = 0;
    for (int i = 0; i < 16; i++) {
      if (s & (1<<i)) {
        b = turn(b, i);
      }
    }
    if (b == goal) {
      printf("%d\n", __builtin_popcount(s));
      for (int i = 0; i < 16; i++) {
        if (s & (1<<i)) {
          printf("%d %d\n", i/4+1, i%4+1);
        }
      }
      break;
    }
  }

  return 0;
}