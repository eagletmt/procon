#include <iostream>
using namespace std;

int main()
{
  int k;
  cin >> k;
  for (int i = 2; i < k; i++) {
    switch (i) {
      case 11: cout << "23 * 89" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 23: cout << "47 * 178481" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 29: cout << "233 * 1103 * 2089" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 37: cout << "223 * 616318177" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 41: cout << "13367 * 164511353" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 43: cout << "431 * 9719 * 2099863" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 47: cout << "2351 * 4513 * 13264529" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 53: cout << "6361 * 69431 * 20394401" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;
      case 59: cout << "179951 * 3203431780337" << " = " << (1LL<<i)-1LL << " = ( 2 ^ " << i << " ) - 1" << endl; break;

    }
  }
  return 0;
}