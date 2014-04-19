#include <iostream>
#include <cmath>
using namespace std;

int main()
{
  double a_phi, a_theta, b_phi, b_theta;
  while (cin >> a_theta >> a_phi >> b_theta >> b_phi && a_phi >= 0) {
    static const double R = 6378.1;
    a_theta *= M_PI/180.0; a_phi *= M_PI/180.0;
    b_theta *= M_PI/180.0; b_phi *= M_PI/180.0;

    const double a_x = R*cos(a_theta)*cos(a_phi);
    const double a_y = R*cos(a_theta)*sin(a_phi);
    const double a_z = R*sin(a_theta);
    const double b_x = R*cos(b_theta)*cos(b_phi);
    const double b_y = R*cos(b_theta)*sin(b_phi);
    const double b_z = R*sin(b_theta);

    const double dot = a_x*b_x + a_y*b_y + a_z*b_z;
    const double rad = acos(dot / (R*R));
    const double ans = R * rad;
    cout << lround(ans) << endl;
  }
  return 0;
}
