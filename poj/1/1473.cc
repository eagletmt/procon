#include <iostream>
#include <sstream>
#include <cstdio>
#include <cmath>
using namespace std;

int main(void)
{
  static const double sq2 = sqrt(2.0)/2.0;

  string s;
  int i = 1;
  while (getline(cin, s) && s != "END") {
    double x = 0, y = 0;
    istringstream iss(s);
    int n;
    while (iss >> n) {
      string d;
      char c;
      while (iss >> c && c != ',' && c != '.') {
        d += c;
      }
      
      if (d == "N") { y += n; }
      else if (d == "NE") { x += n*sq2; y += n*sq2; }
      else if (d == "E") { x += n; }
      else if (d == "SE") { x += n*sq2; y -= n*sq2; }
      else if (d == "S") { y -= n; }
      else if (d == "SW") { x -= n*sq2; y -= n*sq2; }
      else if (d == "W") { x -= n; }
      else if (d == "NW") { x -= n*sq2; y += n*sq2; }
    }
    printf("Map #%d\n", i++);
    printf("The treasure is located at (%.3f,%.3f).\n", x, y);
    printf("The distance to the treasure is %.3f.\n\n", hypot(x, y));
  }
  return 0;
}
