#include <iostream>
#include <vector>
#include <map>
using namespace std;

map<string,int> make_haab_mons()
{
  map<string,int> m;
  m.insert(make_pair("pop", 0));
  m.insert(make_pair("no", 1));
  m.insert(make_pair("zip", 2));
  m.insert(make_pair("zotz", 3));
  m.insert(make_pair("tzec", 4));
  m.insert(make_pair("xul", 5));
  m.insert(make_pair("yoxkin", 6));
  m.insert(make_pair("mol", 7));
  m.insert(make_pair("chen", 8));
  m.insert(make_pair("yax", 9));
  m.insert(make_pair("zac", 10));
  m.insert(make_pair("ceh", 11));
  m.insert(make_pair("mac", 12));
  m.insert(make_pair("kankin", 13));
  m.insert(make_pair("muan", 14));
  m.insert(make_pair("pax", 15));
  m.insert(make_pair("koyab", 16));
  m.insert(make_pair("cumhu", 17));
  m.insert(make_pair("uayet", 18));
  return m;
}

int from_haab(int day, const string& mon, int year)
{
  static const map<string,int> haab_mons = make_haab_mons();
  return year*365 + haab_mons.find(mon)->second*20 + day;
}

pair<pair<int,string>,int> to_tzolkin(int n)
{
  static const string tbl[] = {"imix", "ik", "akbal", "kan", "chicchan", "cimi", "manik", "lamat", "muluk", "ok", "chuen", "eb", "ben", "ix", "mem", "cib", "caban", "eznab", "canac", "ahau"};
  const int year = n / 260;
  n %= 260;
  const string mon = tbl[n % 20];
  const int day = (n % 13) + 1;
  return make_pair(make_pair(day, mon), year);
}

int tmain()
{
  for (int i = 0; i < 20; i++) {
    const pair<pair<int,string>,int> r = to_tzolkin(i);
    cout << r.first.first << ' ' << r.first.second << ' ' << r.second << endl;
  }
  return 0;
}

int main()
{
  int N;
  cin >> N;
  cout << N << endl;
  while (N-- > 0) {
    int day, year;
    string mon;
    char c;
    cin >> day >> c >> mon >> year;
    const pair<pair<int,string>,int> r = to_tzolkin(from_haab(day, mon, year));
    cout << r.first.first << ' ' << r.first.second << ' ' << r.second << endl;
  }
  return 0;
}
