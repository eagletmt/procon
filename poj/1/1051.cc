#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using namespace std;

char decode_morse(int code, int n)
{
#define RETURN(i,c) case i: return c
  switch (n) {
    case 1:
      switch (code) {
        RETURN(0, 'E');
        RETURN(1, 'T');
      }
    case 2:
      switch (code) {
        RETURN(1, 'A');
        RETURN(0, 'I');
        RETURN(3, 'M');
        RETURN(2, 'N');
      }
    case 3:
      switch (code) {
        RETURN(4, 'D');
        RETURN(6, 'G');
        RETURN(5, 'K');
        RETURN(7, 'O');
        RETURN(2, 'R');
        RETURN(0, 'S');
        RETURN(1, 'U');
        RETURN(3, 'W');
      }
    case 4:
      switch (code) {
        RETURN(8, 'B');
        RETURN(10, 'C');
        RETURN(2, 'F');
        RETURN(0, 'H');
        RETURN(7, 'J');
        RETURN(4, 'L');
        RETURN(6, 'P');
        RETURN(13, 'Q');
        RETURN(1, 'V');
        RETURN(9, 'X');
        RETURN(11, 'Y');
        RETURN(12, 'Z');
        RETURN(3, '_');
        RETURN(5, ',');
        RETURN(14, '.');
        RETURN(15, '?');
      }
  }
#undef RETURN
}

string decode(string s)
{
  static string morse[] = {
    ".-", "-...", "-.-.", "-..", ".", "..-.", "--.",
    "....", "..", ".---", "-.-", ".-..", "--", "-.",
    "---", ".--.", "--.-", ".-.", "...", "-", "..-",
    "...-", ".--", "-..-", "-.--", "--.."};
  static int len[] = {
    2, 4, 4, 3, 1, 4, 3,
    4, 2, 4, 3, 4, 2, 2,
    3, 4, 4, 3, 3, 1, 3,
    4, 3, 4, 4, 4};

  vector<int> nums(s.size());
  string morse_code;
  for (int i = 0; i < s.size(); i++) {
    switch (s[i]) {
      case '_':
        nums[i] = 4;
        morse_code += "..--";
        break;
      case ',':
        nums[i] = 4;
        morse_code += ".-.-";
        break;
      case '.':
        nums[i] = 4;
        morse_code += "---.";
        break;
      case '?':
        nums[i] = 4;
        morse_code += "----";
        break;
        
      default:
        nums[i] = len[s[i]-'A'];
        morse_code += morse[s[i]-'A'];
    }
  }
  reverse(nums.begin(), nums.end());

  string decoded;
  int ptr = 0;
  for (int i = 0; i < s.size(); i++) {
    int c = 0;
    for (int j = 0; j < nums[i]; j++, ptr++) {
      c = (c<<1) | (morse_code[ptr] == '-');
    }
    decoded += decode_morse(c, nums[i]);
  }
  return decoded;
}

int main(void)
{
  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    string s;
    cin >> s;
    cout << i+1 << ": " << decode(s) << endl;
  }
  return 0;
}
